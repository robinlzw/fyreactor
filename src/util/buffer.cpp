/************************************************************************/
/*
create time:	2015/6/10
athor:			���Ծ
discribe:		�򵥻�����
*/
/************************************************************************/

#include <util/buffer.h>
#include <math.h>

namespace fyreactor
{

	CBuffer::CBuffer()
		: m_pBuf(new char[INIT_BUFFER_SIZE])
		, m_iSize(INIT_BUFFER_SIZE)
		, m_iLen(0)
	{
	}

	CBuffer::~CBuffer()
	{
		if (m_pBuf != NULL)
		{
			delete[]m_pBuf;
			m_pBuf = NULL;
		}
	}

	bool CBuffer::AddBuf(const char* msg, uint32_t len)
	{
		if (m_iLen + len > MAX_MESSAGE_LEGNTH)
			return false;

		if (m_iSize >= m_iLen + len)
		{
			memcpy(m_pBuf + m_iLen, msg, len);
			m_iLen += len;
		}
		else
		{
			m_iSize = NextPowerOf2(m_iLen + len);
			char* newBuf = new char[m_iSize];

			memcpy(newBuf, m_pBuf, m_iLen);
			memcpy(newBuf + m_iLen, msg, len);

			delete[]m_pBuf;
			m_pBuf = newBuf;
			m_iLen += len;
		}


		return true;
	}

	const char* CBuffer::PopBuf(uint32_t& len)
	{
		len = m_iLen;
		m_iLen = 0;
		return m_pBuf;
	}

	uint32_t CBuffer::NextPowerOf2(uint32_t n)
	{
		double dLog2 = log2(n);
		uint32_t iLog2 = (uint32_t)dLog2 + 1;
		uint32_t ret = exp2(iLog2);

		return ret;
	}
}

