#Wedi

###Assignment

Create a script, which launches a text editor. The script will remember, which files from which folder were edited through the script. The script will choose a file to edit based on the following criteria.

1. If a file was specified, it will be edited.
2. If a file wasn’t specified, the following selection applies:
  1. If multiple files were edited by the script in the specified folder, the latest one that still exists will be chosen.
  2. If the argument `-m` was used, the most frequently edited file in thr given folder will be chosen.
  3. If no files were edited before the given folder, it’s an error situation.
  4. If no folder was specified, the current folder is assumed.
3. The script can also print out the list of all files which were edited by the script in the specified folder before.
4. If the argument `-b` or `-a` was specified, the script will display a list of files, which were edited after `DATE` in format `YYYY-MM-DD`.

####Configuration

1. The script remembers the information about the files it opened in a file given by variable `WEDI_RC`. This variable must be set and accessible.
2. The script launches the editor specified inside the variable `EDITOR`. If not specified, the script uses variable `VISUAL`. If not specified either, it’s an error.

####Return value

1. The script returns success in case of a successful operation. If the editor returns an error, the script returns the same error code. Internal script error is accompanied by an error message.

####Usage

- `wedi [FOLDER]`
- `wedi -m [FOLDER]`
- `wedi FILE`
- `wedi -l [FOLDER]`
- `wedi -b|-a DATE [FOLDER]`
