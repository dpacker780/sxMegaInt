# sxMegaInt: 

This is a header-only C++ template big-int class based on std::bitset. I created it for a few reasons (A) Curiousity to learn how big-int type classes could be created and work. (B) With few examples out there, seeing if std::bitset could actually fulfill the job (Yes!), and (C) It took a lot of scouring to figure out how to implement the algorithms for binary math, especially divide.  You'd think their would be more of them out there, but there are fewer than you realize, and often they have 64-bit constraints.

This was created in: C++20, though adapting to C++17 should be simple enough, there aren't any signficiant dependencies on '20.

Example - creating a 2048 bit number and doing 300 factorial.

```
sxMegaInt<2048> ans8 = 300;
for(int i = 299; i > 0; i--) {
    ans8 *= i; 
}

std::cout << ans8.to_decimal() << "\n\n";

RESULT:

306057512216440636035370461297268629388588804173576999416776741259476533176716867465515291422477573349939147888701726368864263907759003154226842927906974559841225476930271954604008012215776252176854255965356903506788725264321896264299365204576448830388909753943489625436053225980776521270822437639449120128678675368305712293681943649956460498166450227716500185176546469340112226034729724066333258583506870150169794168850353752137554910289126407157154830282284937952636580145235233156936482233436799254594095276820608062232812387383880817049600000000000000000000000000000000000000000000000000000000000000000000000000

```
