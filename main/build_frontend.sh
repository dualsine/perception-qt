#!/bin/bash

get_sha() {
	echo $(find internal_scheme_frontend -type f -printf "%s %p %TY-%Tm-%Td %TH:%TM:%TS %Tz\n" | sha1sum | xargs)
}

NEW_SHA=$( get_sha )
OLD_SHA=$(cat internal_scheme_frontend.sha | xargs)

echo $NEW_SHA
echo $OLD_SHA

if [ "$NEW_SHA" != "$OLD_SHA" ]; then
	cd internal_scheme_frontend
	npm run build
	cd ..
	NEW_SHA=$( get_sha )
	echo $NEW_SHA > internal_scheme_frontend.sha
fi

