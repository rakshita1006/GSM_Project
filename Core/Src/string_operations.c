/*
 * string_operations.c
 *
 *

 */
int convert_integer_to_char(int num, char *str)
{
	int temp=count_intlength(num);
	if(num == 0)
	{
		*str  = '0';
		return 0;
	}
	switch(temp)
	{
		case 5:
			*str++ = num/10000 + 0x30;
			num =  num%10000;
		case 4:
			*str++ = num/1000 + 0x30;
			num =  num%1000;
		case 3:
			*str++ = num/100 + 0x30;
			num =  num%100;
		case 2:
			*str++ = (num/10) + 0x30;
			num =  num%10;
		case 1:
			*str++ = num + 0x30;
			num=0;
			break;
        default:
        	*str = '/0';
        	return 0;
	}
	return 1;
}

/*brief: function valid for maximum 5 digits numbers*/

int convert_negative_int_to_char(int num, char *str, int length)
{

	if(num < 0)
	{
		num=num*(-1);
		*str++ = '-';
	}
	else
	{
		*str= '/0';
		return 0;
	}

	switch(length)
	{
		case 5:
			*str++ = num/10000 + 0x30;
			num =  num%10000;
		case 4:
			*str++ = num/1000 + 0x30;
			num =  num%1000;
		case 3:
			*str++ = num/100 + 0x30;
			num =  num%100;
		case 2:
			*str++ = (num/10) + 0x30;
			num =  num%10;
		case 1:
			*str++ = num + 0x30;
			num=0;
			break;
        default:
        	*str = '/0';
        	return length;
	}
	//}
	return length;

}



int convert_char_to_integer_buff(char* string, int* ptr, int length)
{

//
//	if(*string = '\0')
//	{
//		return 0;
//	}

	switch(length-1)
	{

	    case 5:
			*ptr++ = (*string++ - 48);

		case 4:
			*ptr++ = (*string++ - 48);
//			string++;
//			ptr++;

		case 3:
			*ptr++ = (*string - 48);
			string++;

		case 2:
			*ptr++ =(*string++ - 48);

		case 1:
			*ptr++ = (*string++ - 48);

			break;
        default:
        	return 0;
	}
	return 1;
}

int convert_char_to_integer(char* string, int* ptr, int length)
{
	if(*string == '\0')
	{
		return 0;
	}

	switch(length-1)
	{
	    case 5:
	    	*ptr += ((*string++ - '0') * 10000);
		case 4:
	    	*ptr += ((*string++ - '0') * 1000);
		case 3:
	    	*ptr += ((*string++ - '0') * 100);
		case 2:
			*ptr += ((*string++ - '0') * 10);
		case 1:
			*ptr += ((*string++ - '0'));
     		break;
        default:
        	return 0;
	}
	return length-1;
}

int str_comp_count(char* Source_Ram_address, char* Destination_Ram_address, int length)
{

for(int i=0;i<=length-1;i++)
{
	if(*Source_Ram_address++ !=*Destination_Ram_address++)
	{
		return 0;
	}
}
return 1;
}

int str_comp_dilimetr(char* Source_Ram_address,char* Destination_Ram_address,char dili)
{
	while(*Source_Ram_address != dili)
	{
		if(*Source_Ram_address++ != *Destination_Ram_address++)
		{
			return 0;
		}
	}
	return 1;

}


void str_copy_delmt(char* Source_Ram_address, char* Destination_Ram_address,char dili)
{
	while(*Source_Ram_address != dili)
	{
		  *Destination_Ram_address++= *Source_Ram_address++;
//		   Destination_Ram_address++;
//		   Source_Ram_address++;
	}
}

int str_comp_dilli_n_len(char* Source_Ram_address, char* Destination_Ram_address,char dili, int length)
{
	if (length!=0)
	{
		while(*Source_Ram_address != '\0')
		{
			if(*Source_Ram_address++ != *Destination_Ram_address++)
					{
						return 0;
					}
		}
	}
	else
			{
		while(*Source_Ram_address != ',')
		{
			if(*Source_Ram_address++ != *Destination_Ram_address++)
					{
						return 0;
					}


		}
}
	return 1;
}

int count_intlength(int num) //int* length)
{
	int count=0;

	while(num!=0)
	{
		num =num/10;
		count++;

}
//	*length=count;
	return count;
}

int* JumpStringDillimeter(char* string)
{
	int count =0;

	while(count != 3)
	{
		*string++;
	if (*string == ',')
	{
		count++;
	}

//	return 1;
}
	return string;
	//return 0;
}
//int count_stringlength(char str) //int* length)
//{
//	int count=0;
//
//	while(num!=0)
//	{
//		num =num/10;
//		count++;
//
//}
////	*length=count;
//	return count;
//}



