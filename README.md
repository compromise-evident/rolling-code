Run it: ```apt install g++ geany libgmp-dev```. Open the .cpp in Geany.<br>
Append ```-lgmp``` to Geany's compile & build commands. Hit F9 once. F5 to run.

<p align="center">
  <img src="https://raw.githubusercontent.com/compromise-evident/rolling-code/refs/heads/main/Other/Terminal.png">
</p>

<br>
<br>

## How it works

<p align="center">
  <img src="https://raw.githubusercontent.com/compromise-evident/rolling-code/refs/heads/main/Other/How_it_works.png">
</p>

<br>
<br>

## Pose cryptographic difficulty

"Near which private prime, will I find these public gaps?"
is at least as statistically strong as semiprime factorization.
For example, file "private_seeds" can be the key while the
generated randomness can be ciphertext.
Or you can start fresh with the following resources.

<br>
<br>

## DIY

https://github.com/compromise-evident/WhatNot/blob/main/see_consecutive_primes_and_gaps_following_n.cpp

https://github.com/compromise-evident/WhatNot/blob/main/see_natural_log_of_n.cpp

https://github.com/compromise-evident/WhatNot/blob/main/see_the_prime_following_n.cpp

<br>
<br>

## Sample: consecutive gaps following a 200-digit prime

```text
36
468
336
588
1200
660
168
754
146
1230
94
836
274
140
294
90
526
224
234
892
14
760
282
260
220
258
422
88
104
360
1380
42
178
486
636
86
250
120
218
126
228
930
1318
354
108
230
1270
206
672
142
782
546
924
46
194
48
1402
300
1356
2
1062
280
2330
198
40
416
162
178
26
1206
1342
150
1016
856
228
1472
1066
212
52
26
1108
212
52
1772
78
592
294
12
68
46
66
264
204
446
156
262
6
320
586
798
```

<br>
<br>

## Sample: consecutive gaps following a 1,000-digit prime

```text
122
1560
168
148
4140
1640
1252
30
842
2326
498
7254
3642
104
2904
1170
1030
4092
1368
7422
1268
4750
5030
2376
2952
958
1290
42
1394
2740
344
1552
1998
1484
6
1344
318
3012
5476
990
8372
1372
2502
2648
910
2220
5456
10546
1998
366
152
12
1500
5328
3030
1332
1182
2538
5550
810
1416
3102
228
10
1472
1624
3270
1394
630
2004
2356
2930
1770
322
1118
1804
176
276
490
1898
786
792
144
2344
1572
2582
208
210
10260
1094
318
942
3618
1396
2504
556
2052
720
1512
242
```
