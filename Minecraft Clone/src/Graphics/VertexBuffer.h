#pragma once

class VertexBuffer {
public:
	VertexBuffer(unsigned int size);
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void UploadData(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_Id;
};
