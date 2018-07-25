#include "picture.h"
picture::picture(int num_block_rows,int num_block_cols, pixelData** d)
{
	m_num_block_rows = num_block_rows;
	m_num_block_cols = num_block_cols;
	
	m_blocks = new *block[num_block_rows];
	int dim = block::getDim();
	for(int i=0;i<num_block_rows;i++)
	{
		m_blocks[i] = new block[num_block_cols];
		for(int j=0;j<num_block_cols)
		{
			pixelData* data = &d[i*dim][j*dim];//?
			m_blocks[i][j].setData_Copy(&data)
		}
	}
}
picture::~picture();
{
	for(int i=0; i<m_num_block_rows;i++)
	{
		delete[] m_blocks[i];
	}
	delete[] m_blocks;
}
block** picture::getData()
{
	return m_blocks;
}
int picture::getNumOfRows()
{
	return m_num_block_rows;
}
int picture::getNumOfCols()
{
	return m_num_block_cols;
}