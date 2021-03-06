Using The Analog Signal Builder Module {#usingflasb}
======================================

\tableofcontents

Introduction to Analog Signal Builder Module {#usingflasb_intro}
============================================

The Analog  Signal Builder  (ASB) Falaise module  aims to  process the
truth hits generated by  the SuperNEMO simulation program (flsimulate)
and stored in the `SD` bank of the simulated event record, in order to
modelize  the analog  response  of  the detector  in  terms of  signal
waveforms  with a  realistic shape  and amplitude,  including possible
pile-up effects, noisy baselines.  The characteristics of the computed
modeled analog  signals are  stored in  a new  bank, namely  `SSD` for
further use by the digitization module.

The  figure below  illustrates the  workflow of  the ASB  module.  The
module embeds  a collection of  analog signal generator  drivers which
are responsible to build the analog  signal models from the truth hits
provided by  the simulation  program.  The library  implements several
signal  generator  drivers  specialized for  different  categories  of
detectors and contexts:  signal from optical module  hits, signal from
geiger drift cells...

![asb-img-workflow-1](./images/img-workflow-1.png?raw=true)


The model of  analog signal are objects that contains all informations
needed to generate, on demand, a functor object which associates
a given time to a signal amplitude (Volt). Such an object
is invoked by the digitization module in order to compute
the trigger primitives associated to hits in the detector
(timestamp, crossing of threshold) as well as the sampled waveform
and its associated properties (charge, amplitude...).
The functor object and/or the shape
of the analog signal is not stored by itself in the output data, because
it would be inefficient and expensive (in terms of storage)
to use this approach. The stored informations  generally consist in
a limited set of parameters (identifier of the shape model,
start time of the signal, its risetime and falltime, the peak amplitude...).
Piled-up signals (summed-up signal with delay) are also supported though
dedicated *multi/combined-signal* objects.

The figure below illustrates the typical structure of a modeled analog signal
with its caracteristics and also the functor *f(t)* which can be instantiated
and used  at digitization stage:

![asb-img-analog-signal-1](./images/img-analog-signal-1.png?raw=true)
