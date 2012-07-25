msgpack-autosplit(8) -- A tool to safely rotate msgpack log files
=================================================================

## SYNOPSIS

`msgpack-autosplit` `--dir=<directory>` [<options>]

## DESCRIPTION
Since records in a msgpack stream are not delimited by linefeeds, tools
such as logrotate(8) can not safely rotate the output without  breaking
arbitrary records.

msgpack-autosplit  reads  a  MessagePack  stream  from  standard input,
writes this stream to disk, and safely rotates the disk  file  when  it
reaches a maximum size or after a maximum delay.

You´d  rather use Fluent. Fluent is awesome. But, well, sometimes,
Fluent not an option.


## OPTIONS

  * -d, --dir=<directory>: set the target directory.  All log files are
    written  to this directory.  As msgpack-autosplit makes this direc‐
    tory the current  directory,  it  should  not  be  removed  without
    restarting msgpack-autosplit.

  * -F, --max-files=<N>:  create  at  most  N  files.  Older files are
    purged from disk if more than this number of log files exist.

  * `-h`, `--help`: show usage.

  * -S, --max-space=<N>: use at most N  bytes  of  disk space.  Older
    files are purged from disk if they exceed this limit.

  * -s, --soft-limit=<bytes>: set the file size limit after which a log
    rotation will occur.

  * -t, --rotate-after=<seconds>: trigger a rotation  after  this  many
    seconds.

  * -z, --compress=<compressor>:  compress data using compressor. Only
    gzip is currently implemented.

  * -V, --version: display software version.

## SIMPLE USAGE EXAMPLE

    $ msgpack-autosplit -d /var/log/queries

## ADVANCED USAGE EXAMPLE

    $ msgpack-autosplit -d /var/log/queries -s 1000000 -t 86400 -z gzip -S 20000000
