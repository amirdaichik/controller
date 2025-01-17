#include "block.h"

static void block::setDim(int dim)
{
	s_dim = dim;
}
static void block::setPara(int para)
{
	s_numOfParall = para;
}
block::block()
{
	for(int i=0;i<NUM_OF_DIRECTIONS;i++)
	{
		m_data[i] = new *pixelData[s_dim];
		for(int j=0;j<s_dim;j++)
		{
			m_data[i][j] = new pixelData[s_dim];
			for(int k=0;k<s_dim;k++)
			{
				m_data[i][j][k].r = 0;
				m_data[i][j][k].g = 0;
				m_data[i][j][k].b = 0;
			}
		}
	}
	m_curData = m_data[RIGHT];
}
block::block(const block& b)
{
	m_curDirection = b.m_curDirection
	for(int i=0;i<NUM_OF_DIRECTIONS;i++)
	{
		m_data[i] = new *pixelData[s_dim];
		for(int j=0;j<s_dim;j++)
		{
			m_data[i][j] = new pixelData[s_dim];
			for(int k=0;k<s_dim;k++)
			{
				m_data[i][j][k].r = b.m_data[i][j][k].r;
				m_data[i][j][k].g = b.m_data[i][j][k].g;
				m_data[i][j][k].b = b.m_data[i][j][k].b;
			}
		}
	}
}
block::~block()
{
	for(int i=0;i<NUM_OF_DIRECTIONS;i++)
	{
		for(int j=0;j<s_dim;j++)
		{
			delete[] m_data[i][j];
		}
		delete[] m_data[i];
	}
}
block& block::operator=(const block& b)
{
	m_curDirection = b.m_curDirection;
	for(int i=0;i<NUM_OF_DIRECTIONS;i++)
	{
		for(int j=0;j<s_dim;j++)
		{
			for(int k=0;k<s_dim;k++)
			{
				m_data[i][j][k].r = b.m_data[i][j][k].r;
				m_data[i][j][k].g = b.m_data[i][j][k].g;
				m_data[i][j][k].b = b.m_data[i][j][k].b;
			}
		}
	}
}
bool block::turnData(direction wantedDirection)
{
	bool wasTurned = false;
	int numOfTimesToTurn = (wantedDirection - m_curDirection)%NUM_OF_DIRECTIONS;
	for(int i=0;i<numOfTimesToTurn;i++)
	{
		turn90();
		wasTurned = true;
	}
	m_curDirection = wantedDirection;
	return wasTurned;
}
static bool block::turn90_comp(pixelData** source,pixelData** dest,int s_dim)
{
	pixelData** tmpBlock;
	if(source == dest)
	{
		tmpBlock = new *pixelData[s_dim];
		tmpBlock[0] = new pixelData[s_dim*s_dim];
		for(int i=0;i<s_dim;i++)
			tmpBlock[i] = tmpBlock[0] + s_dim*i;
	}
	else
		tmpBlock = dest;
	for(int y=0;y<s_dim;y++)
	{
		for(int x=0;x<s_dim;x++)
		{
			int newX = s_dim - y - 1;
			int newY = x;  
			tmpBlock[newY][newX].r = data[y][x].r;
			tmpBlock[newY][newX].g = data[y][x].g;
			tmpBlock[newY][newX].b = data[y][x].b;
		}
	}
	if(source == dest)
	{
		for(int i=0;i<s_dim;i++)
		{
			for(int j=0;j<s_dim;j++)
			{
				dest[i][j].r = tmpBlock[i][j].r;
				dest[i][j].g = tmpBlock[i][j].g;
				dest[i][j].b = tmpBlock[i][j].b;
			}
			delete[] tmpBlock[i];
		}
		delete[] tmpBlock;
	}
}
bool block::turn90()
{
	m_curDirection = (m_curDirection+1)%NUM_OF_DIRECTIONS;
}
bool block::setData_noCopy(pixelData** d)
{
	m_data[RIGHT] = d;
	adjust_m_data();
}
bool block::setData_Copy(pixelData** d)
{
	for(int i=0;i<s_dim;i++)
	{
		for(int j=0;j<s_dim;j++)
		{
			m_data[RIGHT][i][j].r = d[i][j].r;
			m_data[RIGHT][i][j].g = d[i][j].g;
			m_data[RIGHT][i][j].b = d[i][j].b;
		}
	}
	adjust_m_data();
}
void block::adjust_m_data()
{
	for(int i=1;i<NUM_OF_DIRECTIONS;i++)
	{
		turn90_comp(m_data[i-1],m_data[i],s_dim);	
	}
}
pixelData** block::getData()
{
	return m_data[m_curDirection];
}