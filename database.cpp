#include "database.hpp"

Database* Database::instance = nullptr;

Database::Database()
{
    setPath();
    loadData();
    msg = msg->getInstance();
}

Database::Database(QListWidget *wdList)
{
    this->wdList = wdList;
    Database();
}

Database* Database::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Database();
    }

    return instance;
}

UserData Database::getData(const int index)
{
    return list.at(index);
}

void Database::updateView()
{
    if(wdList != nullptr)
    {
        wdList->clear();
        for(int i = 0; i < list.size(); i++)
        {
            UserData data = list.at(i);
            std::string text = data.getText().toStdString();
            if(text.size() > MAX_ROW_SIZE)
            {
                text = text.substr(0, MAX_ROW_SIZE);
                text += " . . .";
            }

            text = std::regex_replace(text, std::regex("\n"), " ");
            QString row = QString(std::to_string(i + 1).c_str()) + ": " + text.c_str();
            wdList->addItem(row);
        }
    }
}

void Database::updateDatabase()
{
    list.clear();
    loadData();
    if(wdList)
        updateView();
}

void Database::setView(QListWidget *wdList)
{
    this->wdList = wdList;
    updateView();
}

void Database::loadData()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_location.c_str());

    if(result)
    {
        pugi::xml_node records = doc.child("records");

        for(pugi::xml_node record = records.child("record"); record; record = record.next_sibling("record"))
        {
            UserData usd(record.attribute("date").value(), record.child_value("text"));
            list.insert(list.end(), usd);
        }
    }
    else
    {
        msg->displayMessage("data.xml parsed with error!");
        std::cerr << "data.xml parsed with error!" << std::endl;
    }
}

void Database::setPath()
{
#ifdef WIN
    std::string appdata = getenv("APPDATA");
    location = appdata + "\\torar\\";
    file_location = location + "data.xml";
#else
    std::string appdata = getenv("HOME");
    loc = appdata + "\\.torar\\";
    floc = loc + "data.xml";
#endif

    if(!boost::filesystem::exists(location))
    {
        if(!boost::filesystem::create_directory(location))
        {
            msg->displayMessage("Unable to create directory");
            std::cerr << "Unable to create directory" << std::endl;
        }
        else
        {
            std::cout << "Directory created" << std::endl;
        }
    }

    if(!boost::filesystem::exists(file_location))
    {
        try
        {
            pugi::xml_document doc;

            auto decNode = doc.append_child(pugi::node_declaration);

            decNode.append_attribute("version") = "1.0";
            decNode.append_attribute("encoding") = "utf-8";

            doc.append_child("records").append_child(pugi::node_pcdata);

            auto success = doc.save_file(file_location.c_str());

            if(!success)
            {
                std::string err("Unable to create data.xml at: ");
                err += location;
                msg->displayMessage(QString(err.c_str()));
                std::cerr << "Unable to create " << "data.xml" << " at: " << location << std::endl;
            }
        }
        catch(std::ios::failure e)
        {
            std::string err(e.what());
            std::cerr << err << std::endl;
            msg->displayMessage(QString(err.c_str()));
        }
    }
    std::cout << "Location: " << location << std::endl;
}

size_t Database::indexOf(const std::string date)
{
    for(size_t i = 0; i < list.size(); i++)
    {
        if(list[i].getDate() == date)
            return i;
    }

    throw std::exception("Unable to find index!");
}

void Database::addData(UserData data)
{
    if(list.size() < MAX_LIST_SIZE)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(file_location.c_str());

        if(result)
        {
            pugi::xml_node records = doc.child("records");
            pugi::xml_node record = records.append_child("record");

            record.append_attribute("date").set_value(data.getDate().c_str());

            pugi::xml_node text = record.append_child("text");
            text.append_child(pugi::node_pcdata).set_value(data.getText().toUtf8());

            if(doc.save_file(file_location.c_str()))
            {
                list.insert(list.end(), data);
                if(wdList)
                    updateView();
            }
        }
        else
        {
            msg->displayMessage("data.xml parsed with error!");
            std::cerr << "data.xml parsed with error!" << std::endl;
        }
    }
    else
    {
        msg->displayMessage("You can store only 7500 items!");
        std::cerr << "You can store only 7500 items!" << std::endl;
    }
}

void Database::editData(UserData Data)
{
    try
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(file_location.c_str());

        if(result)
        {
            size_t index = indexOf(Data.getDate());
            list[index].setText(Data.getText());

            pugi::xml_node records = doc.child("records");

            for(pugi::xml_node record = records.child("record"); record; record = record.next_sibling("record"))
            {
                if(record.attribute("date").value() == Data.getDate())
                {
                    record.child("text").text().set(Data.getText().toUtf8().toStdString().c_str());
                    if(!doc.save_file(file_location.c_str()))
                    {
                        msg->displayMessage("Unable to save file!");
                        std::cerr << "Unable to save file!" << std::endl;
                    }

                    updateView();
                    break;
                }
            }
        }
        else
        {
            msg->displayMessage("data.xml parsed with error!");
            std::cerr << "data.xml parsed with error!" << std::endl;
        }
    }
    catch(std::exception e)
    {
        std::string err(e.what());

        msg->displayMessage(QString(err.c_str()));
        std::cerr << err << std::endl;
    }
}

void Database::removeData(UserData data)
{
    try
    {
        size_t index = indexOf(data.getDate());

        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(file_location.c_str());

        if(result)
        {
            pugi::xml_node records = doc.child("records");

            for(pugi::xml_node record = records.child("record"); record; record = record.next_sibling("record"))
            {
                if(record.attribute("date").value() == data.getDate())
                {
                    records.remove_child(record);
                    list.erase(list.begin() + index);
                    if(wdList)
                        updateView();

                    if(!doc.save_file(file_location.c_str()))
                        std::cerr << "Unable to save file!" << std::endl;
                    break;
                }
            }
        }
        else
        {
            msg->displayMessage("data.xml parsed with error!");
            std::cerr << "data.xml parsed with error!" << std::endl;
        }
    }
    catch(std::exception e)
    {
        std::string err(e.what());

        msg->displayMessage(QString(err.c_str()));
        std::cerr << err << std::endl;
    }
}

void Database::removeData(const int index)
{
    try
    {
        removeData(list.at(index));
    }
    catch(std::out_of_range e)
    {
        std::string err(e.what());

        msg->displayMessage(QString(err.c_str()));
        std::cerr << err << std::endl;
    }
}
