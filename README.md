### Run it

```apt install g++ geany```. Open the .cpp in Geany. Hit F9 once. F5 to run.

<br>

### Terminal

```text
Just once, drop/enter any file, preferably one with many random bytes.
(Creates a rolling-seed file containing the SHA3-512 hash of your file).
|
```

<br>

### How it works

```text
SHA3-512 of a seed doubled side-by-side: a2d0cbdc486623fc2f0428e7fbefe5ca4a636af...

1st 16 hex are converted to base 10: 11732101176268039164 mod 256 = pseudorandom byte.

That hash becomes the new seed. Start again to get another byte.
```

<br>

### DIY

https://github.com/compromise-evident/what-not/blob/main/zero_dependency_SHA_single_lines.cpp

https://github.com/compromise-evident/what-not/blob/main/zero_dependency_SHA-256.cpp

https://github.com/compromise-evident/what-not/blob/main/zero_dependency_SHA-512.cpp

https://github.com/compromise-evident/what-not/blob/main/zero_dependency_SHA3-256.cpp

https://github.com/compromise-evident/what-not/blob/main/zero_dependency_SHA3-512.cpp
