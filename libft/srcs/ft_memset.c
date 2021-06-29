#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*p_dest;

	p_dest = destination;
	if (n != 0)
	{
		while (n-- != 0)
			*p_dest++ = (unsigned char)c;
	}
	return (destination);
}
