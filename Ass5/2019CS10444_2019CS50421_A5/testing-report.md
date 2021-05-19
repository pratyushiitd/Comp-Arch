## Testing:

**Anirudha Kulkarni : 2019CS50421**
**Pratyush Saini : 2019CS10444**

### 1.  Verification of example given in Problem statement with respect to our implementation

![](image/testing-report/1621272952458.png)

Explaination:

![](image/testing-report/1621272838567.png)

### 2. Multi core starving:

There can be a case when a core never leaves the MRM and keeps on sending request to MRM due to algorithmic bias. Hence we have starving limit on each core after which the core must get lower priority and release the MRM.

![](image/testing-report/1621270866228.png)

Here we have a lot of DRM requests from Core #1. And as the core #1 is giving algorithmic benefit of lesser clock cycles core #2 was likely to be starved. But by handeling starvation in we see change in cycle 153 to 154 that Row 1 is loaded into row buffer which corresponds to Core #2

![](image/testing-report/1621272239871.png)

Again after resolving starving we change back to algorithmically most beneficial request that is corresponding to core #1.

![](image/testing-report/1621271951158.png)

Hence finally :

![](image/testing-report/1621272441466.png)

![](image/testing-report/1621272455239.png)

### 3. Lookahead for increased throughput:

Input:

![](image/testing-report/1621274057895.png)

![](image/testing-report/1621274073345.png)

Working:

![](image/testing-report/1621274109651.png)

Without lookahead:

![](image/testing-report/1621274143768.png)

With Lookahead:

![](image/testing-report/1621274170715.png)

### 4. Exception in case of infinite loop / unbounded recurssion:

Consider this case:

![](image/testing-report/1621266889806.png)

Output is an exception:

![](image/testing-report/1621267032697.png)

### 5. Exception in a Core should not affect others:

consider core 1 as with invalid input exception:

![](image/testing-report/1621275089546.png)

core 2 as:

![](image/testing-report/1621275105685.png)

We have exception raised for Core #1:

![](image/testing-report/1621275121510.png)

But the other program executes completely:

![](image/testing-report/1621275136107.png)

### 6. Maximizing throughput by parallel processing:

Input of core 1:

![](image/testing-report/1621269024311.png)

Input of core 2:

![](image/testing-report/1621269059803.png)

Input of core 3:

![](image/testing-report/1621269077362.png)

Finally

![](image/testing-report/1621269090580.png)
![](image/testing-report/1621269111068.png)

### 7.

Input of core 1:

![](image/testing-report/1621269521852.png)

Input of core 2:

![](image/testing-report/1621269544618.png)

Input of core 3:

![](image/testing-report/1621269558603.png)

Input of core 4:

![](image/testing-report/1621269573858.png)

Throughput, IPC and total instructions:

![](image/testing-report/1621269587113.png)

![](image/testing-report/1621269598485.png)

#### Exceptions:

1. Out of bound access:

```bash
main:
   sw $s0, 100000000000($s0)
```

![](image/report/1618054536576.png)

2. Non existent register:

```bash
main:
   addi $s9, $s12, 12
```

![](image/testing-report/1621269870733.png)

3. Invalid instruction:

```bash
main:
   sw5 $s0, 1024
```

![](image/testing-report/1621269850059.png)

4. Invalid Branch:

```bash
main:
  j abc
```

![](image/testing-report/1621269820593.png)

5. Invalid syntax of instruction:

```bash
main:
   addi $s0, $s1, $s2
```

![](image/testing-report/1621269835158.png)
