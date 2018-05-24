from m5.params import *
from m5.proxy import *
from MemObject import MemObject

class SimpleMemobj(MemObject):
	type = 'Simple Memobj'
	cxx_header = "hello_world/simple_memobj.hh"
	
	inst_port = SlavePort("CPU side port, receives requests")
	data_port = SlavePort("CPU side port, receives requests")
	mem_side = MasterPort("Memory side port, sends requests")
	