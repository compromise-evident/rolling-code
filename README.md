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

* A seed is loaded and its SHA3-512 hash is taken.
* Pseudorandom byte = the first 16 hex of that hash in base 10, mod 256.
* That hash becomes the new seed. Start again to get another byte.

<br>

### DIY

https://github.com/compromise-evident/what-not/blob/main/zero_dependency_SHA_single_lines.cpp

https://github.com/compromise-evident/what-not/blob/main/zero_dependency_SHA-256.cpp

https://github.com/compromise-evident/what-not/blob/main/zero_dependency_SHA-512.cpp

https://github.com/compromise-evident/what-not/blob/main/zero_dependency_SHA3-256.cpp

https://github.com/compromise-evident/what-not/blob/main/zero_dependency_SHA3-512.cpp

<br>

### Analyze the pseudorandom bytes file

https://github.com/compromise-evident/what-not/blob/main/ref.cpp
