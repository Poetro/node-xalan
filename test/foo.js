var xalan = require("../xalan");

xalan.initialize();
xalan.transform("foo.xml", "foo.xsl", "foo-out.xml");
