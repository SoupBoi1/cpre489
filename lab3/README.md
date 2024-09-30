# CPR E 4890 Lab 3 Skeleton Code

This folder contains a makefile and a template C file. You can compile your
program using the makefile:

```bash
make
```

and run it with the format:

```bash
./udp-forwarder <SOURCE_IP> <SOURCE_PORT> <DESTINATION_IP> <DESTINATION_PORT> <LOSS_RATE>
```

It is up to you to implement the behavior defined by the lab manual (including
handling arguments).

By default, almost all errors and warnings will prevent your program from
compiling. It is generally a good idea to leave this on. However, if you want to
live dangerously, you may disable this by removing the `Wfatal-errors` compiler
flag from the makefile.

## Testing Your Program

You can use `cvlc` and `vlc` to test your program by using it as follows.

To generate a source video stream directed towards `<SRC_IP>:<SRC_PORT>`:

```bash
cvlc --repeat test.mp4 --sout '#standard{access=udp,mux=ts,dst=SRC_IP:SRC_PORT}'
```

To play your video on the receiving address, `<DEST_IP>:<DEST_PORT>`:

```bash
vlc -vvv udp://@<DEST_IP>:<DEST_PORT>
```

**IMPORTANT**: `<SRC_PORT>` and `<DEST_PORT>` should be different! Your program
will receive from `<SRC_PORT>` and send to `<DEST_PORT>`. If they're the same,
you will be circumventing your program entirely.
