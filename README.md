# kbdtab_sniffer

## about

A quick and dirty "printf debugging" app to see what is comming out from the kbdtab device in plan9 / 9front.

As is it prints out the contents of received string aray with some decoding and some test logic to recognize CTRL + UP / DOWN, ENTER and DELETE key combinations or key preses.

Code based on the riow program from 9front.

## why

Need to for improvement of another plan9 & 9front project ([plan9-rchistory](https://github.com/Nailim/plan9-rchistory)). Feel free to modify and abuse.

## installation

### build

`mk`

### install

Installs to user folder $home/bin/$objtype.

`mk install`

### uninstall

Removes from user folder.

`mk uninstall`

### configuration

The following line should be inserted in *$home/bin/rc/riostart* file:

`</dev/kbdtap kbdtab_sniffer >/dev/kbdtap`

If you're having issues with additional windows on startup, you can put the previous definition on to a separate script and call that from riostart file.

For example, create a script srw as *$home/bin/rc/sniffer*:

```
#!/bin/rc

# sniffer
# start kbdtab_sniffer

</dev/kbdtap kbdtab_sniffer >/dev/kbdtap
```

And then call the script in *$home/bin/rc/riostart* file:

`window sniffer`

### IMPORTANT

Makse sure you run rio with scroll enabled (flag -s), or it will block keyboard input untill the output window is scrolled to allow all the text to be printed.

Run this from the command line to start rio OR edit your $HOME/lib/profile file to match:

`rio -i riostart -s`

