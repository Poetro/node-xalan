import Options
from os import unlink, symlink, popen
from os.path import exists

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  
  #conf.check(lib="xalan-c", uselib_store="xalan", mandatory=True)
  #conf.check(lib="xerces-c", uselib_store="xerces", mandatory=True)

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.target = "xalan"
  obj.source = "xalan.cpp"
  obj.linkflags = ['-L/opt/local/lib','-static -lxerces-c', '-lxalan-c']

def shutdown():
  if Options.commands['clean']:
    if exists('xalan.node'): unlink('xalan.node')
  else:
    if exists('build/default/xalan.node') and not exists('xalan.node'):
      symlink('build/default/xalan.node', 'xalan.node')

