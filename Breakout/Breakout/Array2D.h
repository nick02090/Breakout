#pragma once
namespace util 
{
	/// <summary>
	/// Custom 2D array class.
	/// </summary>
	class Array2D
	{
	public:
		/// <summary>
		/// Constructor for the custom 2D array class.
		/// </summary>
		/// <param name="_rows">Number of rows</param>
		/// <param name="_cols">Number of columns</param>
		Array2D(int _rows, int _cols) : rows(_rows), cols(_cols) 
		{
			data = new int[rows * cols];
		}
		~Array2D()
		{
			delete[] data;
		}
		/// <summary>
		/// Returns the value at the given position in the array.
		/// </summary>
		/// <param name="row">Row selector</param>
		/// <param name="col">Column selector</param>
		/// <returns></returns>
		int& at(int row, int col)
		{
			return data[row * rows + col];
		}
	private:
		int rows;
		int cols;
		int* data;
	};
}