#!/usr/bin/env bash

set -u

ROOT_DIR="$(cd -- "$(dirname -- "$0")/.." && pwd)"
MSH_BIN="$ROOT_DIR/minishell"
TMP_DIR="$(mktemp -d /tmp/minishell-builtins-tests.XXXXXX)"

PASS_COUNT=0
FAIL_COUNT=0
CASE_OUT=""
CASE_ERR=""
CASE_EC=0
CASE_NAME=""
CASE_FAILED=0

cleanup() {
	rm -rf "$TMP_DIR"
}

pass() {
	printf "PASS: %s\n" "$1"
	PASS_COUNT=$((PASS_COUNT + 1))
}

fail() {
	printf "FAIL: %s\n" "$1"
	FAIL_COUNT=$((FAIL_COUNT + 1))
	CASE_FAILED=1
}

assert_exit_code() {
	local expected="$1"
	if [ "$CASE_EC" -ne "$expected" ]; then
		fail "$CASE_NAME -> exit code esperado $expected, obtenido $CASE_EC"
	fi
}

assert_err_contains() {
	local text="$1"
	if ! grep -Fq -- "$text" "$CASE_ERR"; then
		fail "$CASE_NAME -> stderr no contiene: $text"
	fi
}

assert_out_contains() {
	local text="$1"
	if ! grep -Fq -- "$text" "$CASE_OUT"; then
		fail "$CASE_NAME -> stdout no contiene: $text"
	fi
}

assert_out_regex_count() {
	local regex="$1"
	local expected="$2"
	local count

	count="$(grep -Ec -- "$regex" "$CASE_OUT" || true)"
	if [ "$count" -ne "$expected" ]; then
		fail "$CASE_NAME -> regex [$regex] esperado $expected, obtenido $count"
	fi
}

run_case() {
	local name="$1"
	local input="$2"
	local expected_exit="$3"
	local clean_env="${4:-0}"

	CASE_NAME="$name"
	CASE_OUT="$TMP_DIR/$name.out"
	CASE_ERR="$TMP_DIR/$name.err"
	CASE_EC=0
	CASE_FAILED=0

	if [ "$clean_env" -eq 1 ]; then
		printf "%b" "$input" | env -i PATH="$PATH" "$MSH_BIN" >"$CASE_OUT" 2>"$CASE_ERR"
	else
		printf "%b" "$input" | "$MSH_BIN" >"$CASE_OUT" 2>"$CASE_ERR"
	fi
	CASE_EC=$?
	assert_exit_code "$expected_exit"
	if [ "$CASE_FAILED" -eq 0 ]; then
		pass "$CASE_NAME"
	fi
}

run_pwd_deleted_dir_case() {
	local tmpd

	tmpd="$TMP_DIR/pwd_deleted_dir"
	mkdir -p "$tmpd"
	run_case "pwd_deleted_dir" \
		"cd $tmpd\n/bin/rmdir $tmpd\npwd\nexit\n" \
		1
	assert_err_contains "minishell: pwd:"
	if [ "$CASE_FAILED" -eq 0 ]; then
		pass "$CASE_NAME assertions"
	fi
}

trap cleanup EXIT

if [ ! -x "$MSH_BIN" ]; then
	printf "Compilando minishell...\n"
	if ! make -C "$ROOT_DIR" >/dev/null; then
		printf "No se pudo compilar minishell\n"
		exit 1
	fi
fi

run_case "exit_non_numeric" "exit abc\n" 2
assert_err_contains "numeric argument required"
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "exit_sign_only" "exit +\n" 2
assert_err_contains "numeric argument required"
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "exit_negative_wrap" "exit -1\n" 255

run_case "exit_too_many_args" "exit 7 8\npwd\nexit\n" 0
assert_err_contains "too many arguments"
assert_out_contains "$ROOT_DIR"
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "cd_home_not_set" "cd\nexit\n" 1 1
assert_err_contains "HOME not set"
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "cd_invalid_path" "cd /definitely/not/here\nexit\n" 1
assert_err_contains "No such file or directory"
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "cd_dash_roundtrip" "cd /tmp\ncd -\npwd\nexit\n" 0
assert_out_contains "$ROOT_DIR"
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_pwd_deleted_dir_case

run_case "echo_flags" "echo -nn hi\necho hi-there\nexit\n" 0
assert_out_contains "himinishell >"
assert_out_contains "hi-there"
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "env_builtin_with_arg" "env EXTRA\nexit\n" 1
assert_err_contains "too many arguments"
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "export_unset_cycle" \
	"export FOO=bar\n/usr/bin/env\nunset FOO\n/usr/bin/env\nexit\n" \
	0
assert_out_regex_count "^FOO=bar$" 1
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "env_builtin_lists_exported" \
	"export FOO=bar\nenv\nunset FOO\nenv\nexit\n" \
	0
assert_out_regex_count "^FOO=bar$" 1
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "export_invalid_identifier" "export 1A=2\nexit\n" 1
assert_err_contains "not a valid identifier"
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "unset_invalid_identifier" "unset 1A\nexit\n" 1
assert_err_contains "not a valid identifier"
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

run_case "export_without_value" "unset ZZZ\nexport ZZZ\n/usr/bin/env\nexit\n" 0
assert_out_regex_count "^ZZZ=$" 1
if [ "$CASE_FAILED" -eq 0 ]; then
	pass "$CASE_NAME assertions"
fi

printf "\nResumen tests builtins: PASS=%d FAIL=%d\n" "$PASS_COUNT" "$FAIL_COUNT"
if [ "$FAIL_COUNT" -ne 0 ]; then
	exit 1
fi
exit 0
