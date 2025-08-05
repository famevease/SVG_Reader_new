#pragma once

#include "../SVGElement.h"
#include <vector>
#include <utility>
#include <string>

typedef std::vector<std::pair<std::string,std::string>> Attributes;  

/**
 * @brief A composite class that contains a vector of shape pointers
 * (polymorphic).
 *
 * The Group class is derived from the SVGElement class and defines a group of
 * SVGElements. The Group class is a composite class that contains a vector of
 * SVGElement pointers (polymorphic). The Group class is used to group
 * SVGElements together.
 */

class Group : public SVGElement
{
public:
	Group();


    Group(Attributes attributes);

    ~Group() override;

    /**
     * @brief Gets the type of the shape.
     *
     * @return The string that represents the type of the shape.
     */
    std::string getClass() const override;

    /**
     * @brief Gets the attributes of the shape.
     *
     * @note This function uses rapidXML to parse the SVG file and get the
     * attributes of the shape.
     *
     * @return The attributes of the shape that parsed from the SVG file.
     */
    Attributes getAttributes() const; 

    /**
     * @brief Adds a shape to the composite group.
     *
     * @param shape The shape to be added to the composite group.
     */
    void addElement(SVGElement* shape) override;

    /**
     * @brief Gets the vector of shapes in the composite group.
     *
     * @return The vector of shapes in the composite group.
     */
    std::vector<SVGElement*> getElements() const;

    void printData() const override;
	Vector2Df getMinBound() const override;
    Vector2Df getMaxBound() const override;
    std::vector<std::string> getTransforms() const override;
	SVGElement* getParent() const override;

private:
    std::vector<SVGElement*> shapes;  
    Attributes attributes;              
};

