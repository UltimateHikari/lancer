DB=db/lancer.db
EXEC=build/src/lancer

test:
	cp $(DB) build/tests/ && echo "test db prepared"

package:
	mkdir -p rls;	\
	cp $(DB) $(EXEC) rls/

cleanup:
	rm -r rls
