<div align="center">
  <h1>What is this all about?</h1>
</div>

<p>This is a straightforward project, replicating linux bash. No leaks. No crashes. <br>
We have to replicate what is requested and make it behave like bash, from exit code to small quirks 

<p>Obviously, we shouldn't do 100% of the bash. We have to do “only” some parts, like: <br>

  - A good Parsing 
  - Redirections (`<`, `>` , `<<` and `>>`)
  - Pipes (only `|`)
  - Handle environment variables (like `$USER` or `$SOMETHING`)
  - Handle $? (exit code)
  - Handle Single quotes and Double quotes
  - Signals (`Ctrl + C`, `Ctrl + D` and `Ctrl + \`)
  - Builtins (Echo, cd, pwd, export, unset, env and exit)

Of course, as you know, the Bash is a complex thing, it's a complex bubble connected to another complex bubble and another bubble... and so on. <br>

So, if you want to make a simple `echo` command it dosent simple prints things, for example, if you want to put a flag, like `echo -n` or put something with expansion, like `echo $USER` or with Single quotes, like `echo $USER`.<br>

As you can see, everything you need to think 3 steps ahead, because of this we choose to implement the binary tree to help with the organization of the processes.  
<div align="center">
  <img src="">
</div>


## Patchnotes

<details>

<div align="center"><h3>Version 1.0.5 - (16/08/2024) </h3></div>
  
--------

- Fixed crash related to `unset OLDPWD` (unset OLDPWD + (cd -- or cd -)) <br>
- Fixed `""` and `''` error display (('' or "") + enter) <br>
- Fixed displaying temp file on heredoc (`echo << a`) <br>
- Fixed an occasion problem with quotes when expanding (`export a='"'` + `echo $a$USER`) <br>
- Fixed a problem with double expansion <br>

---------
</details>
