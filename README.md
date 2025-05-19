###  Basic database project

Pour cloner le project:
`git clone --recursive https://github.com/chemin.vers.repos.git`

Si jamais vous ne voyez pas zig.exe dans Tools, FoundryTools_windowsx64, faite:
`.\setup.bat`

Pour compiler le project:
`ctrl+shift+b`

Pour debugger le project:
`F5`

```mermaid

erDiagram
    CHARACTERS {
        int CharacterID
        string Name
        string Job
    }
    OBJECTS {
        int ObjectID
        string Name
        string Description
    }
    CLIENTS {
        int ClientID
        string Name
        string Email
    }
    PRODUCTS {
        int ProductID
        string Name
        float Price
    }
    ORDERS {
        int OrderID
        date DateOrder
    }
    CATEGORIES {
        int CategorieID
        string Name
    }


    CHARACTERS ||--o{ ORDERS : "does"
    CLIENTS ||--o{ ORDERS : "makes"
    ORDERS ||--o{ PRODUCTS : "contains"
    PRODUCTS ||--o{ CATEGORIES : "belongs to"
    OBJECTS ||--o{ CHARACTERS : "owns"

```

