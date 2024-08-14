## Patchnotes

<details>

<div align="center"><h3>Version 1.0.5 - (15/08/2024) </h3></div>
  
--------

- Fixed crash related to `unset OLDPWD` (unset OLDPWD + (cd -- or cd -)) <br>
- Fixed `""` and `''` error display (('' or "") + enter) <br>
- Fixed displaying temp file on heredoc (`echo << a`) <br>
- Fixed an occasion problem with quotes when expanding (`export a='"'` + `echo $a$USER`) <br>

---------
</details>
