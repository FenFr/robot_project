# this works with linux
VERZEICHNIS    := $(shell pwd | sed s_.*/__)
QT_PROJECTFILE := $(VERZEICHNIS).pro
# this works with qt4
QT_MAKEFILE    := Makefile
# das steht irgendwo in der projektdatei
exe-filename   := $(VERZEICHNIS)

.PHONY: no_qt_default
no_qt_default: .gitignore
	@make --no-print-directory -f $(QT_MAKEFILE)

# abhängig von dieser Datei, zufällig gerade makefile
.gitignore: makefile
	@echo -n > $@
	@echo >> $@ "/\.gitignore"
	@echo >> $@ "/*\.pro"
	@echo >> $@ "/$(QT_MAKEFILE)"
	@echo >> $@ "/*\.o"
	@echo >> $@ "/$(exe-filename)"

# regression tests
repeat::
	@make
repeat::
	@./interface 0
repeat::
	@./interface 2534
# wait some time for bluetooth
	@sleep 1
repeat::
	@./interface 2534 nonblock
# wait some time for bluetooth
	@sleep 1

# automatically remade
$(QT_MAKEFILE): $(QT_PROJECTFILE)
	@echo "creating $@"
	@qmake -o $(QT_MAKEFILE)

define update-if-changed
$1: | $1-temp
$1-temp:
# wenn $1 nicht existiert, dann ganz normal erstellen
ifeq ($(strip $(wildcard $1)),)
	@touch $$@
else
	@mv $1 $$@
endif
	@make -s $1
	@diff --ignore-matching-lines='^#' $$@ $1 && mv $$@ $1 || true
	@rm -f $$@
endef

$(QT_PROJECTFILE):
#	@qmake -project LIBS+=-lbluetooth QMAKE_CXXFLAGS+=-std=gnu++11
	@qmake -project LIBS+=-lbluetooth

$(eval $(call update-if-changed,$(QT_PROJECTFILE)))

.PHONY: qtclean
qtclean: $(QT_MAKEFILE)
	@make -s distclean
	@rm -f $(QT_PROJECTFILE)

.PHONY: veryclean
veryclean: qtclean
	@rm -f .gitignore

# include Makefile targets
%: $(QT_MAKEFILE) force
	@make -s -f $< $@

.PHONY: force
force: ;
