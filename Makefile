.PHONY: release

DIR=Week01
EXEC=warm-up

release:
	(mv $(DIR) $(EXEC) && \
	zip -r ~/$(EXEC).zip $(EXEC) && \
	mv $(EXEC) $(DIR))