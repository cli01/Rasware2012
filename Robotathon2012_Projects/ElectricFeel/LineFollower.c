
void LineFollower (void) {
		signed char right = 10, left = 10;	//Motor values	
		int lsArray[8];						//Array of line sensor inputs


		while(1) {
		int sum = 0;
		unsigned char lsByte = ReadLineSensor();	//Read from linesensor
		unsigned char temp;
		int i;
		int k;\
		int j = -3;
		
		for(i = 0; i < 8; i++) {
		 	temp = ~lsByte;				//Invert the input for negative logic
			lsArray[i] = (temp & 0x01);	//Get the last bit
			lsArray[i] = j * lsArray[i];//Multiply by the input by weight
			lsByte = lsByte >> 1;		//Shift to isolate the last bit for next loop
			if (i != 3) {j++;}			//Calibrate the weight
										//Weight: (-3, -2, -1, 0, 0, 1, 2, 3)
		}
		
		for(k = 0; k < 8; k++) {
			sum += lsArray[k];			//Add the sum of the weights
		}
		
		//Caliberate the motor powers accordingly with the weights
		if (sum < 0) {
			left = 70 - sum * 7;
			right = 30 + sum * 3;
		}
		
		else if (sum > 0) {
			right = 70 + sum * 7;
			left = 30 - sum * 3;
		}
		
		else if (sum == 0) {
			left = 70;
			right = 70;
		}
		
		//Set the motor to appropriate power
		SetMotorPowers(right, left);
	}
}
