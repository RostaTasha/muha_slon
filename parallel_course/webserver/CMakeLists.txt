cmake_minimum_required(VERSION 2.8)	 # �������� ������ CMake.
										# ���� ������ ������������ ���������
										# ������ ��������, ��������� ��������� �����.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")								
										
project(final)			# �������� �������

set(SOURCE_EXE main.cpp)		# ��������� ���������� �� ������� ���������� ��� ������������ �����

find_package (Threads)

add_executable(final ${SOURCE_EXE})	# ������� ����������� ���� � ������ final

target_link_libraries(final ${CMAKE_THREAD_LIBS_INIT})		# �������� ��������� � �����������