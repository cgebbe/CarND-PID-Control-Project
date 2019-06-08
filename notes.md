
Constructor (...
	Kp = 0
	Kd = 0
	Ki = 0

	cte_last = 0 ?!
	cte_int = 0
	error = 0
)
	

get_steering_angle(double cte)

	// calculate time derivatives or integratives of cte
	dt = 1 // assuming equi-distant spacing between sensor measurements
	cte_diff = (cte - cte_last) / dt
	cte_int += cte
	error += pow(cte,2)
	
	steer_angle = -Kp * cte - Kd * cte_diff - Ki * cte_int
	return steer_angle


get 


# Solutions from other students

https://medium.com/intro-to-artificial-intelligence/pid-controller-udacitys-self-driving-car-nanodegree-c4fd15bdc981
https://medium.com/@cacheop/pid-control-for-self-driving-1128b42ab2dd

1. Get good intial values by  first setting Kp, then Kd, then Ki
	- "trail-and-error-method", see also https://en.wikipedia.org/wiki/File:PID_Compensation_Animated.gif
	-> starting values e.g. Kp=0.05, Kd=1.5, Ki=0.0001
2. Get optimal values using twiddle algorithm or SGD
	-> need to modify main.cpp to reset course after N number of steps!


# How to reset simulator

You would somehow send a message via websocket to reset the simulator or to start and stop it.
However, at least I didn't find anything like that...

Relevant links:
https://github.com/udacity/self-driving-car-sim/issues/75
https://github.com/udacity/self-driving-car-sim/issues/37


# Alternative: Do it for exactly one track round
It would be good to do the experiment for one round.
Therefore you need to know where you are in the track.
However, the received json message only contains information about:
1. cte
2. image
3. speed
4. steering_angle
5. throttle

So this is not feasible. Instead, perform the experiment for a number of steps....

Basically: 
if (cnt<num_steps) {
	drive
}
else {
	twiddle.update
}



twiddle.update -->

for each param:
	if options_to_
		create new options
			step1 = 0,1,0
			step2 = 0,1,0
	
		for each possible step
			param_test = param+step
			evaluate steps
			if any of them got better
				use new param
				step *= 1.1
			else:
				use old param
				step *= 0.9
			 
		
if there is a result for all experiments
	-> evaluate and setup new experiment
		next param
		
else:
	run next experiment
	
	

Driving with params=0.135369, 1.67486, 0.00012017,  ### current params_step=0.0251671, 0.505421, 3.36947e-05, , idx_current_params=1 --> result=156.654



=== Set up new experiments!
Driving with params=0.126795, 2.20375, 0.000190852,  ### current params_step=0.0401265, 0.593396, 4.83507e-05, , idx_current_params=0 --> result=11.3132
Driving with params=0.0866686, 2.20375, 0.000190852,  ### current params_step=0.0401265, 0.593396, 4.83507e-05, , idx_current_params=0 --> result=56.7756
Driving with params=0.166922, 2.20375, 0.000190852,  ### current params_step=0.0401265, 0.593396, 4.83507e-05, , idx_current_params=0 --> result=46.0813
=== Evaluated: original params scored lowest result=11.3132
