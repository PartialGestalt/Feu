/*
 * FeuThingScreen.h
 *
 * FeuThingScreen is a class for the <step> XML element
 */

#ifndef FEUTHINGSCREEN_H_
#define FEUTHINGSCREEN_H_

class FeuThingScreen : public FeuThing {
public:
    FeuThingScreen(TiXmlElement *, FeuThing *parent = NULL);
	~FeuThingScreen();

private:
    FeuCalculable *mCondition; // From the "condition" attribute
    FeuCalculable *mX;
    FeuCalculable *mY;
    FeuCalculable *mZ;

public:
    virtual float getAttributeValue(std::string);
    virtual void  setAttributeValue(std::string,float);

};



#endif /* FEUTHINGSCREEN_H_ */
