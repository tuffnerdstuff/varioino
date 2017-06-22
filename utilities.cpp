#include "utilities.h"
#include <math.h>
#include <stdlib.h>

void getIntString(char *buff, int buffLen, int value)
{
	int digitCount = countDigits(value);
	buff[buffLen-1] = '\0';

	int i = 0;
	for (i = buffLen - 2; i >= 0; i--)
	{
		buff[i] = '0' + (value % 10);
		value /= 10;
	}

}

void getFloatString(char *buff, int buffLen, float value, int n)
{

  int intValue = abs((int)(value * pow(10,n)));
  char sign = value >= 0 ? '+' : '-';
  int digitCount = countDigits(intValue);
  if (digitCount+3 > buffLen)
  {
    int idx;
    for (idx = 0; idx < buffLen-2; idx++)
    {
      buff[idx] = '-';
    }
    buff[idx] = '\0';

  }
  else
  {

    int i;
    int count = 0;
    buff[buffLen-1] = '\0';

    for (i = buffLen - 2; i > 0; i--)
    {
      if (count == n)
      {
        buff[i] = '.';
      }
      else if (intValue <= 0)
      {
        if (count <= n+1)
        {
          buff[i] = '0';
        }
        else
        {
          buff[i] = ' ';
        }

      }
      else
      {
        buff[i] = '0' + (intValue % 10);
        intValue /= 10;
      }

      count++;
    }

    // Sign
    buff[0]=sign;


  }


}

int countDigits(int num)
{
    int n = 0;
    while(num) {
        num /= 10;
        n++;
    }
    return n;
}

float roundNearest(float val, int decim)
{
  float decimFact = pow(10,decim);
  return roundf(val * decimFact) / decimFact;
}

