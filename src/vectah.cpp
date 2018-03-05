//
// Created by karan on 4/3/18.
//

#include "vectah.h"
#include <iostream>

Vectah::Vectah(): m_button("Hello World")   // creates a new button with label "Hello World".
{
    // Sets the border width of the window.
    set_border_width(10);

    // When the button receives the "clicked" signal, it will call the
    // OnButtonClicked() method defined below.
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &Vectah::OnButtonClicked));

    // This packs the button into the Window (a container).
    add(m_button);

    // The final step is to display this newly created widget...
    m_button.show();
}

Vectah::~Vectah()
{
}

void Vectah::OnButtonClicked()
{
    std::cout << "Hello World" << std::endl;
}