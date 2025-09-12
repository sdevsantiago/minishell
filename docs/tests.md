### Multiple redirections

```
cmd > file1 > file2
```
or
```
cmd >> file1 >> file2
```

Should create both `file1` and `file2` but store the output in `file2`

### Environment variables

#### SHLVL

Must be increased by 1 if executed from any other shell or 1 if executed 
