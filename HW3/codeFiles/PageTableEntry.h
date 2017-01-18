class PageTableEntry
{
    public:
    
    PageTableEntry():valid=false,address=NULL {};

    int* get_page_address(){return _address;}; //Pointer to beginning of frame
    void set_page_address(int* adr){_address = adr}; //Set the pointer to a frame
    bool is_valid(){return _valid;}; //Returns whether the entry is valid
    void set_valid(bool valid){_valid = valid;}; //Allows to set whether the entry is valid

    private:
    
    bool _valid;
    int* _address;
};
