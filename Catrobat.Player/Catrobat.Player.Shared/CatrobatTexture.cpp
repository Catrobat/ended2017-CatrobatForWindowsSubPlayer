#include "pch.h"
#include "CatrobatTexture.h"

using namespace std;
using namespace Microsoft::WRL;

CatrobatTexture::CatrobatTexture(vector < vector<int> > alphaMap, ComPtr<ID2D1Bitmap> bitmap)
    : m_bitmap(move(bitmap)), m_alphaMap(alphaMap)
{
    m_height = m_bitmap->GetSize().height;
    m_width = m_bitmap->GetSize().width;
}

CatrobatTexture::~CatrobatTexture()
{
    m_bitmap.Reset();
}

ComPtr<ID2D1Bitmap> CatrobatTexture::GetBitmap()
{
    return m_bitmap;
}

vector < vector<int> > CatrobatTexture::GetAlphaMap()
{
    return m_alphaMap;
}

int CatrobatTexture::GetWidth()
{
    return m_width;
}

int CatrobatTexture::GetHeight()
{
    return m_height;
}
