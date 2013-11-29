#  DON'T EDIT THIS FILE.
#  THIS IS GENERATED BY "Configuration/configure_BuildRule.py".


OBJECTS = \
$(OUTDIR)\.\DriverAPI\Context.obj \
$(OUTDIR)\.\DriverAPI\Device.obj \
$(OUTDIR)\.\DriverAPI\ErrorString.obj \
$(OUTDIR)\.\DriverAPI\Initialize.obj \
$(OUTDIR)\.\RuntimeAPI\Device.obj \
$(OUTDIR)\.\RuntimeAPI\ErrorString.obj \



{.\RuntimeAPI\}.cpp{$(OUTDIR)\.\RuntimeAPI\}.obj::
	IF NOT EXIST $(OUTDIR)\.\RuntimeAPI $(MKDIR) $(OUTDIR)\.\RuntimeAPI
	$(CPP) /c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) /Fo$(OUTDIR)\.\RuntimeAPI\ @<<
$<
<<

{.\DriverAPI\}.cpp{$(OUTDIR)\.\DriverAPI\}.obj::
	IF NOT EXIST $(OUTDIR)\.\DriverAPI $(MKDIR) $(OUTDIR)\.\DriverAPI
	$(CPP) /c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) /Fo$(OUTDIR)\.\DriverAPI\ @<<
$<
<<


install::
	IF NOT EXIST $(INSTALL_DIR)\include\SupportCUDA\. $(MKDIR) $(INSTALL_DIR)\include\SupportCUDA\.
	$(INSTALL) .\*.h $(INSTALL_DIR)\include\SupportCUDA\.
	IF NOT EXIST $(INSTALL_DIR)\include\SupportCUDA\.\DriverAPI $(MKDIR) $(INSTALL_DIR)\include\SupportCUDA\.\DriverAPI
	$(INSTALL) .\DriverAPI\*.h $(INSTALL_DIR)\include\SupportCUDA\.\DriverAPI
	IF NOT EXIST $(INSTALL_DIR)\include\SupportCUDA\.\RuntimeAPI $(MKDIR) $(INSTALL_DIR)\include\SupportCUDA\.\RuntimeAPI
	$(INSTALL) .\RuntimeAPI\*.h $(INSTALL_DIR)\include\SupportCUDA\.\RuntimeAPI
