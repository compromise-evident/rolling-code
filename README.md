Run it: ```apt install g++ geany libgmp-dev```. Open the .cpp in Geany.<br>
Append ```-lgmp``` to Geany's compile & build commands. Hit F9 once. F5 to run.

<br>

<p align="center">
  <img src="https://raw.githubusercontent.com/compromise-evident/rolling-code/refs/heads/main/Other/Terminal.png">
</p>

<br>
<br>

## How it works

<p align="center">
  <img src="https://raw.githubusercontent.com/compromise-evident/rolling-code/refs/heads/main/Other/Formula.png">
</p>

When a random file is dropped/entered as input,
a "private_seeds" file is created, which contains
an n-digit value (whose length you can set via "digit_length".)
That value is loaded and adjusted so that it is prime.
Now, the idea is to find prime gaps following the value,
and compare them to the average prime gap near that value.

If a gap is greater than the average gap, you get a 1 bit, else a 0 bit.
But this REPRODUCIBLY gets you many more 0 bits than 1 bits,
because the average gap is too large. Such an
occurrence is unacceptable for randomness.
And so the average gap is enhanced.
Using the formula above, a gap is then instead
compared to a fraction of the average gap.
As a result, not only do bits 1 & 0 occur nearly equally,
but so do all 256 bytes, as this tool demonstrates.

The same process (randomness of continued gaps) is used
to update the "private_seeds" file with a new n-digit value.
You may alter this value within that file, at any time
(introducing additional sources of randomness.)
After each run, an "analysis" file is generated
about the "random_bytes" file.
It contains bit & byte occurrence, distinct bytes,
total bytes, all the bytes raw, and all the
text bytes for visual.
For values over 200 digits,
the formula yields bit occurrences
of greater equivalence. And that is desirable.
You can adjust the formula in the following line,
which is equivalent to "a/2 + a/7 + a/18",
but you can edit just the 44 and 63 instead.<br>
```int enhanced_average_gap = ((average_gap * 44) / 63);```

<br>
<br>

## Why compare gaps to a fraction of the average gap?

The average of gaps ```12, 10, 14, 10, 16, 14, 12, 200``` is 36.
You see that ~12 is what occurs "normally".
It's the 200 throwing the average off to 36.
So if a gap of "normally 12" is greater than 36,
then random bit is 1. That doesn't happen often.
But you need it to happen, about as often as the opposite,
for good randomness.
Here's an actual list of consecutive prime gaps following
an 800-digit prime, where sudden big gaps throw
the average off to "abnormal" highs.
(Note that the formula only applies
to finding "normal" gaps near values of 200+ digits.)

```text

12818
4902
1734
2316
1324
210
4202
160
804
714
126

```

<br>
<br>

## Why not compare gaps to the previous gap?

To get byte "11111111", you'll need 8 consecutive gaps,
each greater than the one before it. That's extremely rare.
And so are sub-strings of those bits.
See file "do_not_do_this" in Other.
It's a laughable analysis of
50,000 bytes generated using this faulty method.

<br>
<br>

## Cryptographic difficulty

"Near which private prime, will I find these public gaps?"
is at least as statistically strong as semiprime factorization.
Use this if you need to simply pose cryptographic difficulty.
Otherwise, use groupOTP and passOTP for data encryption.

<br>
<br>

## DIY

https://github.com/compromise-evident/WhatNot/blob/main/see_prime_gaps_following_n_using_nextprime.cpp

https://github.com/compromise-evident/WhatNot/blob/main/see_prime_gaps_following_n_using_probab_prime_p.cpp

https://github.com/compromise-evident/WhatNot/blob/main/see_natural_log_of_n.cpp

<br>
<br>

## Auto-generates analysis file about random_bytes file

```text

random_bytes

occurrence of bit 0: 3981
occurrence of bit 1: 4019

occurrence of byte 0: 4
occurrence of byte 1: 4
occurrence of byte 2: 4
occurrence of byte 3: 4
occurrence of byte 4: 5
occurrence of byte 5: 3
occurrence of byte 6: 3
occurrence of byte 7: 2
occurrence of byte 8: 3
occurrence of byte 9: 7
occurrence of byte 10: 6
occurrence of byte 11: 5
occurrence of byte 12: 4
occurrence of byte 13: 2
occurrence of byte 14: 3
occurrence of byte 15: 3
occurrence of byte 16: 5
occurrence of byte 17: 1
occurrence of byte 18: 6
occurrence of byte 19: 5
occurrence of byte 20: 6
occurrence of byte 21: 5
occurrence of byte 22: 6
occurrence of byte 23: 1
occurrence of byte 24: 2
occurrence of byte 25: 5
occurrence of byte 26: 4
occurrence of byte 27: 4
occurrence of byte 28: 3
occurrence of byte 29: 3
occurrence of byte 30: 1
occurrence of byte 31: 2
occurrence of byte 32: 4
occurrence of byte 33: 1
occurrence of byte 34: 6
occurrence of byte 35: 2
occurrence of byte 36: 4
occurrence of byte 37: 3
occurrence of byte 38: 6
occurrence of byte 39: 1
occurrence of byte 40: 2
occurrence of byte 41: 6
occurrence of byte 42: 1
occurrence of byte 43: 5
occurrence of byte 44: 5
occurrence of byte 45: 5
occurrence of byte 46: 1
occurrence of byte 47: 5
occurrence of byte 48: 1
occurrence of byte 49: 5
occurrence of byte 50: 3
occurrence of byte 51: 4
occurrence of byte 52: 2
occurrence of byte 53: 0
occurrence of byte 54: 2
occurrence of byte 55: 4
occurrence of byte 56: 3
occurrence of byte 57: 5
occurrence of byte 58: 4
occurrence of byte 59: 3
occurrence of byte 60: 4
occurrence of byte 61: 3
occurrence of byte 62: 2
occurrence of byte 63: 5
occurrence of byte 64: 2
occurrence of byte 65: 2
occurrence of byte 66: 5
occurrence of byte 67: 1
occurrence of byte 68: 8
occurrence of byte 69: 4
occurrence of byte 70: 4
occurrence of byte 71: 8
occurrence of byte 72: 6
occurrence of byte 73: 3
occurrence of byte 74: 4
occurrence of byte 75: 3
occurrence of byte 76: 1
occurrence of byte 77: 3
occurrence of byte 78: 4
occurrence of byte 79: 2
occurrence of byte 80: 3
occurrence of byte 81: 3
occurrence of byte 82: 4
occurrence of byte 83: 1
occurrence of byte 84: 2
occurrence of byte 85: 2
occurrence of byte 86: 8
occurrence of byte 87: 0
occurrence of byte 88: 7
occurrence of byte 89: 3
occurrence of byte 90: 1
occurrence of byte 91: 3
occurrence of byte 92: 7
occurrence of byte 93: 3
occurrence of byte 94: 5
occurrence of byte 95: 2
occurrence of byte 96: 5
occurrence of byte 97: 4
occurrence of byte 98: 2
occurrence of byte 99: 5
occurrence of byte 100: 1
occurrence of byte 101: 5
occurrence of byte 102: 5
occurrence of byte 103: 4
occurrence of byte 104: 5
occurrence of byte 105: 1
occurrence of byte 106: 3
occurrence of byte 107: 3
occurrence of byte 108: 4
occurrence of byte 109: 6
occurrence of byte 110: 7
occurrence of byte 111: 6
occurrence of byte 112: 5
occurrence of byte 113: 2
occurrence of byte 114: 5
occurrence of byte 115: 4
occurrence of byte 116: 8
occurrence of byte 117: 4
occurrence of byte 118: 6
occurrence of byte 119: 4
occurrence of byte 120: 5
occurrence of byte 121: 2
occurrence of byte 122: 3
occurrence of byte 123: 3
occurrence of byte 124: 5
occurrence of byte 125: 3
occurrence of byte 126: 2
occurrence of byte 127: 3
occurrence of byte 128: 3
occurrence of byte 129: 2
occurrence of byte 130: 6
occurrence of byte 131: 7
occurrence of byte 132: 3
occurrence of byte 133: 6
occurrence of byte 134: 3
occurrence of byte 135: 4
occurrence of byte 136: 5
occurrence of byte 137: 4
occurrence of byte 138: 1
occurrence of byte 139: 1
occurrence of byte 140: 3
occurrence of byte 141: 6
occurrence of byte 142: 4
occurrence of byte 143: 4
occurrence of byte 144: 3
occurrence of byte 145: 3
occurrence of byte 146: 4
occurrence of byte 147: 3
occurrence of byte 148: 3
occurrence of byte 149: 7
occurrence of byte 150: 2
occurrence of byte 151: 3
occurrence of byte 152: 2
occurrence of byte 153: 3
occurrence of byte 154: 2
occurrence of byte 155: 4
occurrence of byte 156: 8
occurrence of byte 157: 4
occurrence of byte 158: 3
occurrence of byte 159: 5
occurrence of byte 160: 2
occurrence of byte 161: 2
occurrence of byte 162: 4
occurrence of byte 163: 6
occurrence of byte 164: 5
occurrence of byte 165: 7
occurrence of byte 166: 1
occurrence of byte 167: 7
occurrence of byte 168: 4
occurrence of byte 169: 2
occurrence of byte 170: 5
occurrence of byte 171: 2
occurrence of byte 172: 6
occurrence of byte 173: 8
occurrence of byte 174: 3
occurrence of byte 175: 7
occurrence of byte 176: 5
occurrence of byte 177: 6
occurrence of byte 178: 5
occurrence of byte 179: 2
occurrence of byte 180: 4
occurrence of byte 181: 5
occurrence of byte 182: 7
occurrence of byte 183: 2
occurrence of byte 184: 6
occurrence of byte 185: 6
occurrence of byte 186: 2
occurrence of byte 187: 3
occurrence of byte 188: 2
occurrence of byte 189: 1
occurrence of byte 190: 5
occurrence of byte 191: 5
occurrence of byte 192: 3
occurrence of byte 193: 3
occurrence of byte 194: 3
occurrence of byte 195: 9
occurrence of byte 196: 8
occurrence of byte 197: 3
occurrence of byte 198: 1
occurrence of byte 199: 3
occurrence of byte 200: 4
occurrence of byte 201: 2
occurrence of byte 202: 5
occurrence of byte 203: 4
occurrence of byte 204: 5
occurrence of byte 205: 5
occurrence of byte 206: 7
occurrence of byte 207: 5
occurrence of byte 208: 6
occurrence of byte 209: 5
occurrence of byte 210: 8
occurrence of byte 211: 5
occurrence of byte 212: 5
occurrence of byte 213: 8
occurrence of byte 214: 3
occurrence of byte 215: 7
occurrence of byte 216: 3
occurrence of byte 217: 6
occurrence of byte 218: 6
occurrence of byte 219: 3
occurrence of byte 220: 4
occurrence of byte 221: 6
occurrence of byte 222: 2
occurrence of byte 223: 5
occurrence of byte 224: 4
occurrence of byte 225: 3
occurrence of byte 226: 0
occurrence of byte 227: 1
occurrence of byte 228: 4
occurrence of byte 229: 4
occurrence of byte 230: 5
occurrence of byte 231: 2
occurrence of byte 232: 3
occurrence of byte 233: 6
occurrence of byte 234: 7
occurrence of byte 235: 5
occurrence of byte 236: 6
occurrence of byte 237: 1
occurrence of byte 238: 4
occurrence of byte 239: 7
occurrence of byte 240: 7
occurrence of byte 241: 2
occurrence of byte 242: 3
occurrence of byte 243: 5
occurrence of byte 244: 3
occurrence of byte 245: 4
occurrence of byte 246: 3
occurrence of byte 247: 6
occurrence of byte 248: 3
occurrence of byte 249: 3
occurrence of byte 250: 4
occurrence of byte 251: 4
occurrence of byte 252: 1
occurrence of byte 253: 2
occurrence of byte 254: 2
occurrence of byte 255: 4

253 distinct, 1000 total

Every byte raw:
223
85
158
18
207
136
66
117
236
245
49
243
159
162
91
163
169
247
211
163
5
68
251
213
151
116
207
50
131
224
86
243
59
96
34
140
127
248
174
50
77
19
195
103
29
208
163
133
254
240
197
178
43
246
165
86
21
164
131
157
103
165
131
125
115
246
24
9
244
128
165
34
49
238
238
187
33
7
224
104
34
241
225
191
86
196
210
175
130
27
182
74
175
119
164
191
199
11
225
88
213
40
234
191
190
38
244
122
157
2
205
82
145
240
70
167
168
66
9
215
38
72
161
205
76
216
255
156
66
101
0
109
80
193
213
61
118
10
116
203
146
190
95
251
60
45
35
69
51
204
175
17
122
102
75
80
187
228
180
9
97
26
146
204
99
47
104
234
70
22
58
114
165
41
215
82
111
124
98
107
16
178
3
209
50
167
37
22
192
86
135
23
219
212
212
103
180
34
131
213
0
36
209
218
151
200
21
159
228
185
170
34
63
205
212
79
146
172
132
117
173
230
20
233
250
235
124
235
19
29
217
187
185
82
61
247
145
225
186
42
111
195
89
5
26
229
232
186
244
51
43
234
170
41
248
144
230
116
196
96
68
115
118
57
156
153
125
11
27
45
144
239
89
130
230
73
221
247
54
86
133
195
214
143
206
38
249
162
172
181
68
4
47
15
56
148
1
255
209
112
124
156
112
92
32
174
177
112
94
113
88
143
84
9
133
177
151
111
236
114
176
59
97
150
98
195
55
41
68
32
44
68
112
239
222
66
210
75
92
108
163
235
240
107
131
14
96
245
149
145
194
99
171
46
174
134
135
38
171
49
160
32
230
56
201
182
240
208
254
51
38
122
105
195
234
127
79
117
243
111
202
94
149
14
216
228
170
134
77
215
119
22
210
208
25
6
102
250
247
165
16
117
136
179
170
224
114
43
233
156
247
147
176
154
124
30
215
15
18
191
4
220
92
142
227
153
10
15
182
251
235
198
210
106
173
45
212
83
86
233
239
68
90
197
49
25
183
11
78
104
181
69
58
127
65
188
36
39
64
218
27
252
153
210
184
239
92
219
164
51
32
37
206
44
118
119
234
20
20
175
217
118
63
207
47
101
149
18
169
173
37
10
218
210
236
116
49
141
242
129
137
140
230
221
155
104
221
135
245
97
181
217
231
75
130
172
99
55
204
220
148
178
211
115
155
149
181
2
63
136
157
149
228
147
159
7
45
176
177
68
144
0
71
223
66
137
60
159
77
19
102
236
218
21
208
206
155
93
199
26
101
184
152
164
48
184
203
31
110
10
120
130
210
6
240
69
73
38
136
120
116
96
102
71
176
217
55
121
63
107
1
204
212
194
215
141
239
183
59
147
36
73
25
45
150
165
173
3
41
242
60
202
108
167
20
28
255
173
167
148
180
2
206
82
72
28
62
138
88
211
133
120
116
106
184
74
156
99
173
88
222
68
223
206
141
5
221
80
142
52
233
217
211
120
108
111
9
181
160
172
200
36
223
177
71
61
143
233
19
241
27
63
156
213
238
4
143
71
202
55
120
161
57
133
215
130
6
44
200
91
162
81
154
235
193
47
103
208
196
16
9
123
164
218
2
99
1
202
100
21
146
220
81
4
189
185
12
57
22
250
196
193
204
156
167
44
182
218
124
172
156
194
234
163
94
104
116
240
114
240
91
180
16
136
246
114
165
141
203
95
43
54
199
219
232
72
10
205
231
13
111
185
93
109
118
126
67
208
177
242
123
72
78
184
71
243
10
8
229
173
20
137
118
128
78
108
213
190
201
196
131
253
243
142
213
22
11
78
102
41
229
9
101
196
253
158
110
110
4
175
250
110
196
12
179
139
214
221
233
210
141
88
175
185
112
12
1
109
101
110
192
92
89
72
84
109
64
178
162
74
56
25
167
141
8
26
72
132
74
85
247
223
119
57
28
182
251
168
35
40
116
94
173
0
71
195
132
52
202
255
110
86
200
16
209
25
190
195
24
128
195
22
113
209
29
166
19
203
92
232
125
109
71
213
149
168
43
130
20
249
163
239
88
207
109
115
229
70
3
47
192
96
70
220
211
65
142
129
14
152
93
158
8
12
249
18
237
224
3
140
239
149
62
236
11
234
69
205
221
18
185
58
134
214
133
137
188
217
172
197
206
88
57
131
34
13
126
177
58
182
216
238
167
236
21
196
159
106
245
135
176
86
157
215
81
97
18
190
94
121
175
195
31
182
168
206
60
110
184
123
207
155
41
248
178
44
191
170
71
92

Only the 97 standard text bytes (9, 10, and 32-126):
UBu1[Dt2V;`"2Mg+Vg}s	"1!h"VJwX(&zRFB	&HLBemP=v
t_<-#E3zfKP	ac/hF:r)Ro|bk2%Vg"$"?Ou|R=*oY3+)t`Dsv9}-YI6V&D/8p|p\ p^qXT	or;ab7)D ,DpBK\lk`c.&1 83&ziOuo^Mwfur+|\
j-SVDZ1NhE:A$'@\3 %,vwv?/e%
t1haKc7s?-DGB<Mf]e0n
xEI&xt`fG7y?k;$I-)<lRH>XxtjJcXDP4xlo	$G=?G7x9,[Q/g	{cdQ9,|^htr[r_+6H
o]mv~C{HNG
vNlNf)	ennnXpmen\YHTm@J8HJUw9#(t^G4nVq\}mG+XmsF/`FA]>E:X9"~:jVQa^y<n{),G\

```

<br>
<br>

## My other tools which use rolling-code

* Authorship (not yet using the latest version)
* groupOTP (not yet using the latest version)
* passOTP (not yet using the latest version)
