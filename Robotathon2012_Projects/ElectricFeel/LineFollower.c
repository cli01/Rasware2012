
void LineFollower (void) {
		char right = 10, left = 10;	
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
			j++;
		}
		
		for(k = 0; k < 8; k++) {
			sum += lsArray[k];
		}
		
		if (sum < 0) {
			left = 30 + (-1) * sum * 9;
			right = 30 - sum * 3;
		}
		
		if (sum > 0) {
			right = 30 + sum * 10;
			left = 30 - sum * 3;
		}
		
		if (sum == 0) {
			left = 40;
			right = 40;
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