<p align="center">
  <img src="https://raw.githubusercontent.com/compromise-evident/rolling-code/main/Other/Terminal_ff69c1f0f76ba895294509a31af27137.png">
</p>

<br>
<br>

# File "RC_seeds" overwritten per roll >>>

```text
3148240471146814294320320752931626367018153782717717901366572504878914391649032625250736974142133601333260784215992030563053337272320577190921333661773077377764257528856527617935542504271820346053200713611026101763691451143989119436074469203275191925121204030516905662443244042870296011930717058270481821649206382615674836150976603005223050273509068818461651581977891565362143802524761403843241815148148107773221949331393687707317249612151220693371491675916681168030976614702863772681619536355917771234053644831295803612121731204730215470223346109201413296097513391476994182869120114026714911220073343419464243110883659013334226564067111762410362776522647820641236605834270164381912518523701134859060160512674618729289443672568497174089527032086541992689232229349425576910950774982599125864104579511923256621291454060217314828719110346836671608363408164538741642537552801780754577133509998342312770001068610661394171731520378774332824129176211229275440930232451348821540101850100732992255041752242134



PRIVATE! DO NOT SHARE!

```

Seeds are 100 mostly 10-digit values strung together.
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

# For absolutely absurd cryptanalysis protection...

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

# Breaking news July 2024

* Memory is zeroed when allocated and freed.

`init_on_alloc` and `init_on_free` has hit most Linux distros and growing.
Although a plus for security, no more RAM garbage for supplementing randomness.
I'll have to either replace or remove this feature here and in all my repos using rolling-code and related randomness supplement....
