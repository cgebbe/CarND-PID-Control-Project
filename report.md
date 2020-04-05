## Describe the effect of the P, I and D component of the PID algorithm!

The steering angle is determined based on the cross track error (CTE), i.e. the distance between the egovehicle position and the ideal path.
More exactly, the steering angle is determined as a sum of three terms:

- one term which is proportional to the CTE (P)
- one term which is based on the time derivative of the CTE (D)
- one term which is based on the time integral of the CTE (I)

### P-component

This component can be considered as the main component. Basically, the farther away the car is from the ideal path, the more the greater the steering angle.

However, while a controller using only this term keeps the car on the track, the car always "overshoots" the ideal path, see short video below.

<img src="output_Kp.gif" width="600">

The reason is as follows: When the car reaches the ideal path, the steering angle will be zero. However, due to the previous steering angle, the car's yaw will not be parallel to the ideal path. Thus, it always overshoots.

### D-component

The problem of overshooting can be compensated with the D-term (see video below).

<img src="output_Kp_Kd.gif" width="600">

The idea of the D-compoment can be explained as follows:
If we are getting closer to the ideal path, we already have to reduce the steering angle magnitude (and even countersteer) to align the car's yaw with the ideal path. Since the CTE is decreasing, its time derivative is negative.
In contrast, if we are getting farer way from the ideal path, we would like to steer "harder" to get back on track. In this case the CTE is increasing, meaning its time derivative is positive.
Thus, taking into account the time derivative of the CTE helps to steer better.

### I-component

As the lecture notes discussed, the I-component helps to correct any offset in the system such as erroneous actors.

However, a too high value may cause instability.

## Describe how the final hyperparameters were chosen!

### Manual tuning using systematic method

At first, the parameters were chosen manually by following the method described in https://en.wikipedia.org/wiki/PID_controller#Manual_tuning

1. Set Kp=Ki=Kd=0
2. Increase Kp until the output oscillates
3. Increase Kd to reduce magnitude of oscillations
4. Finally, increase Ki to correct any potential offset (found not to be necessary?!)

By following this approach these values were picked: 
 - Kp = 0.07
 - Kd = 2.0
 - Ki= 0.0001 (very minimal, to allow optimization)

### Further automatic tuning using twiddle algorithm

These values were further optimized using the twiddle algorithm.
The twiddle algorithms works similar to gradient descent by slightly varying one parameter and going in the direction with the lowest cost (in this case cost= sum of sqared CTE).

Ideally, it would work by driving the exact same track with different parameter sets and comparing the results.
However, with the provided simulator it is not possible to drive the "exact same track".
Therefore, we would need to be able to reset the simulator or at least know where in the track we are. Neither of those technical option seem to exist...

Therefore, I tried something else: Instead of driving the whole track, the current parameters were always evaluated after 100 "ticks". Here, 1 tick = one json message sent to the simulator.
The big disadvantage with that approach is that in these 100 ticks, the car will sometimes drive rather easy straight roads and sometimes sharp curves, which were much more likely to result in large CTEs.
Thus, the cost was not so much influenced by the parameters, but instead much more by the track, which the car drove in these 100 ticks.

The result is that my optimization never reaches a final value.
Despite that, one parameter set during the optimization, which yielded qualtiatively good results, was the following:
Kp=0.126795, Kd=2.20375, Ki=0.000190852

Some details concerning the implementation of the twiddle algorithm:
- Instead of evaluating the new param set after each run, I first waited until all potential steps (="experiments") were completed and then picked the one yielding the lowest costs.
- I also always reevaluated the original parameter set in each run, since it just might have been a "lucky" part of the track as a straight line

# Future work in this repo
- For twiddle: Longer evaluation time for each experiment (ideally exactly one track)
- It is likely, that the optimal solution will also overshoot as described in the lecture notes. I believe that an additional regularization term such as the weighted sum of the Kp, Kd, Ki parameters would prevent that
- Currently, the twiddle class uses vectors to store the parameters. Maybe an array would be better here?
- Currently, the twiddle algorithm always performs three experiments: (-1,0,+1)*step . We could potentially dismiss the last one, if the first one already shows better results
