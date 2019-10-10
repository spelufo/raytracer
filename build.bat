@echo off
del raytracer.exe
cl /O2 src\main.cpp /Feraytracer.exe
raytracer.exe img\latest.png