#ifndef  COUNT_CHECK_HPP
# define COUNT_CHECK_HPP

# include <string>

/*	is this stuff stupid
this is just a lot of overhead stuff for checking
just check the cound directly as needed
for errors just give a string of what was checked
*/

struct CountCheck
{
	virtual bool Check(unsigned int val) const = 0;
	virtual std::string ToString() const = 0;
};
struct CountCheckEqual : public CountCheck
{
	unsigned int Val;
	CountCheckEqual(unsigned int val);
	bool Check(unsigned int val) const override;
	std::string ToString() const override;
};
struct CountCheckRange : public CountCheck
{
	unsigned int Min;
	unsigned int Max;
	CountCheckRange(unsigned int min, unsigned int max);
	bool Check(unsigned int val) const override;
	std::string ToString() const override;
};
struct CountCheckModulo : public CountCheck
{
	unsigned int Mod;
	unsigned int Val;
	CountCheckModulo(unsigned int mod, unsigned int val);
	bool Check(unsigned int val) const override;
	std::string ToString() const override;
};

#endif