#include <string.h>
#include <stdio.h>
#include "record.hpp"

#define LEN 1234
using namespace std;


int record::init (const char *n, int p, int g) {
	phone = p;
	group = g;
	if (n) {
		name = std::make_unique<char []> (strlen (n) + 1);
		if (!name) return -1;
			strcpy (name.get(), n);
	}
	else
		name = nullptr;
	return 0;
}

/*record& record::operator=(const record& x) 
{
	if(this == &x) return *this;
	init(x.name.get(), x.phone, x.group);
	return *this;
}*/

/*record::record(const record& x) 
{
	init(x.name.get(), x.phone, x.group);
}*/

read_status record::read (FILE *fp) {
	char buf[LEN];
	name = nullptr;
	if (fscanf (fp, "%s%d%d", buf, &phone, &group) != 3)
	{
		if (feof(fp)) return read_status::eof;
		return read_status::format;
	}
	if (init (buf, phone, group))
		return read_status::memory;
	return read_status::success;
}

void record::print (const ordering order[], FILE *fp)
{
	const int max_items = 3;
	const ordering default_ordering[max_items]= {ordering::name, ordering::phone, ordering::group};
	const ordering * p = (order[0] != ordering::none ? order : default_ordering);
	for (int i = 0; i < max_items; i++)
		switch (p[i])
		{
			case ordering::name:
				fprintf (fp," %s", name.get()); break;
			case ordering::phone:
				fprintf (fp," %d", phone); break;
			case ordering::group:
				fprintf (fp," %d", group); break;
			case ordering::none:
				continue;
		}
	fprintf (fp, "\n");
}

void record::print_r (FILE * fp) {
	fprintf(fp, "%s %d %d\n", name.get(), phone, group);
}