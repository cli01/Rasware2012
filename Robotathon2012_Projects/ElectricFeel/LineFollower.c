
void LineFollower (void) {
		signed char right = 10, left = 10;	
		int lsArray[8];
		unsigned char lsByte;	


		while(1) {
		int sum = 0;
		int lsArray[8];
		unsigned char lsByte = ReadLineSensor();
		unsigned char temp;
		int i;
		int k;
		int l;
		int count;
		int j = -3;
		
		for(i = 0; i < 8; i++) {
		 	temp = ~lsByte;
			lsArray[i] = (temp & 0x01);
			lsArray[i] = j * lsArray[i];
			lsByte = lsByte >> 1;
			if (i != 3) {j++;}
		}
		
		for(k = 0; k < 8; k++) {
			sum += lsArray[k];
		}
		
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
		
		SetMotorPowers(right, left);
		
		if (count % 100 == 0) {
			for(l = 0; l < 8; l++) {
				UARTprintf("%d", lsArray[l]);
			}
			UARTprintf("    ");
			UARTprintf("%d\n", sum);
		}
		
		count++;
	}
}