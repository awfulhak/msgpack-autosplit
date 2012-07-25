Feature: Test maximum space parameter

  Feed msgpack-autosplit enough data to make it purge

  Scenario: start msgpack-autosplit and feed it a lot of data.

    Given a directory named "aruba"
    And a file named "tmp/aruba/msgpack-large.data" with large msgpack data
    When I run `sh -c 'msgpack-autosplit -s 1000 -d logdir-pruned -S 11000 < msgpack-large.data 2>/tmp/y'`
    Then a directory named "logdir-pruned" should exist
    And a file named "logdir-pruned/.current" should exist
    And the number of files for "tmp/aruba/logdir-pruned/*" should be 11.
    And every file for "tmp/aruba/logdir-pruned/*" should be a valid msgpack stream
