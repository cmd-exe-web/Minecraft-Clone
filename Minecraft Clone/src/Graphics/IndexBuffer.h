#pragma once

class IndexBuffer {
public:
	IndexBuffer(unsigned int count);
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void UploadData(const void* data, unsigned int count);
	void Bind();
	void Unbind();

	inline unsigned int GetCount() { return m_Count; }
private:
	unsigned int m_Id;
	unsigned int m_Count;
};
