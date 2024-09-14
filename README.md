Run it: ```apt install g++ geany```. Open the .cpp in Geany. Hit F9 once. F5 to run.

<p align="center">
  <img src="https://raw.githubusercontent.com/compromise-evident/rolling-code/main/Other/Terminal_ff69c1f0f76ba895294509a31af27137.png">
</p>

<br>
<br>

# Seeds overwritten per roll

Seeds are 100 10-digit values strung together.
Both the order of digits, and order of 10-digit values matters;
guessing 100 correct 10-digit values is not enough,
they must be ordered correctly.
There's about [10^157](https://www.wolframalpha.com/input?i=100%21)
different ways to order 100 different items.
Swapping or changing any digits or 10-digit
strings in the seeds file,
not only makes a difference in the code,
but a complete difference--as if a hash.

<br>
<br>

# For absolutely absurd cryptanalysis protection

Set absurd_protection_against_cryptanalysis to true.
It writes only one of 1,000 items from randomness[ ] to file "Code" per round.
It's very slow, and code_length_in_thousands simply becomes "actual code length."
Whether or not you set it to true, if you don't want the code exposed,
communicate only its hash.

<br>
<br>

# Tools using RC

* Authorship
* passOTP
* OTP

<br>
<br>

# RAM garbage?

* Unix_time_supplement randomness sprouts from Unix time and no longer supplemented with RAM garbage.

RAM on Linux is now zeroed when allocated and freed; there's no more garbage.
`init_on_alloc` and `init_on_free` has hit most Linux distros and growing.
