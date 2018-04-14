#pragma once

#include "Core.ECS.Core.Component.h"


namespace nECS {


    class cText :
        public cComponentGeneric
    {
    public:
        typedef  cComponentGeneric  tSuperClass;

    public:
        virtual  ~cText();
        cText();
        cText( const std::string& iVector );
        cText( const cText& iRHS );

        void Build( const std::string& iString );

    public:
        // Copy
        virtual  cComponent* Clone() override;

    public:
        // Access / Set
        const std::string& Text();
        void Text( const std::string& iText );
    };


} // namespace nECS

