
Readline-based command line utility for shell scripting

It is a simple C program that allows you to easily integrate readline
into your shell scripts and shell functions.

== Usage:

----
$ readline -d message.txt -p "Enter message: " -H history
Enter message: Hello
$ cat message.txt
Hello
$ cat history
Hello
----

When you run +readline+ again, "Hello" will be in the history.

----
$ readline -h

readlinesh usage: readline <options...>

 -d <destination>  -- Where to write the line (default stdout)
 -H <history>      -- History file (default ~/.readline-history)
 -p <prompt>       -- The prompt (default "> ")

The line is written to history even on Ctrl-C.
Use Ctrl-D on a blank line to cancel and skip writing to history.
----

== Git-based example

Here is an example of using +readline+ to input your Git commit messages with history and without loading your editor.  Put this shell function in your shell startup scripts:

----m4_include(examples/git-commit.sh)----

Then you can do:
----
$ ls
... directory ...
$ git status
... git information ...
$ gm myfile.c
Enter commit message: This is my change to myfile.c
----

You have full-featured line editing and history without losing your view of the previous output.  If you cancel +gm+ with Ctrl+C or Ctrl+D it will exit cleanly without running +git commit+.

== Installation

Be sure you have the libreadline and libhistory development packages for your system. On Debian and Ubuntu this is APT package +libreadline-dev+.  Then do:

----
$ git clone https://github.com/jmjwozniak/readlinesh.git
$ cd readlinesh
$ ./autogen.sh
$ ./configure --prefix=$HOME/readlinesh
$ make install
# Test:
$ $HOME/readlinesh/bin/readline
----

=== Non-standard libreadline locations

If you have libreadline/libhistory in a non-standard location, such as a from-source installation or an Anaconda environment, use something like:

==== Anaconda

This pattern works for Linux or Mac.

----
$ C=$HOME/path/to/conda"
$ export CFLAGS="-I$C/include"
$ export LDFLAGS="-L$C/lib -Wl,-rpath -Wl,$C/lib"
$ export LIBS="-lhistory"
$ ./configure --prefix=...
$ make install
----

==== Mac Homebrew

----
$ C=/usr/local/opt/readline
$ export CFLAGS="-I$C/include"
$ export LDFLAGS="-L$C/lib"
$ export LIBS="-lhistory"
$ ./configure --prefix=...
$ make install
----

m4_dnl Local Variables:
m4_dnl mode: text;
m4_dnl End:
