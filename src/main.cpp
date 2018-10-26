// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/buildinfo.h>

#include <gdk/camera.h>
#include <gdk/color.h>
#include <gdk/database.h>
#include <gdk/exception.h>
#include <gdk/gameloop.h>
#include <gdk/glfw_wrapper.h>
#include <gdk/input_private.h>
#include <gdk/intvector2.h>
#include <gdk/keyboard.h>
#include <gdk/logger.h>
#include <gdk/model.h>
#include <gdk/mouse.h>
#include <gdk/quaternion.h>
#include <gdk/resources.h>
#include <gdk/resources_private.h>
#include <gdk/shaderprogram.h>
#include <gdk/texture.h>
#include <gdk/time.h>
#include <gdk/time_private.h>
#include <gdk/vector3.h>
#include <gdk/vertexdata.h>
#include <gdk/vertexformat.h>

#include <cmath>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <vector>

static constexpr auto TAG = "main";

using namespace gdk;

namespace
{
    std::vector<std::shared_ptr<gdk::Camera>> cameras;
    
    std::vector<std::shared_ptr<gdk::Model>> models;
}

int main()
{
    std::shared_ptr<gdk::Camera> pCamera = std::make_shared<Camera>([&]()
    {
        Camera camera;

        camera.setViewportSize(0.5, 1.0);
            
        return camera;
    }());

    std::shared_ptr<gdk::Camera> pCamera2 = std::make_shared<Camera>([&]()
    {
        Camera camera;

        camera.setViewportSize(0.5, 1.0);
        camera.setViewportPosition(0.5, 0.0);
        camera.setClearColor(Color::Blue);
            
        return camera;
    }());

    cameras.push_back(pCamera);
    cameras.push_back(pCamera2);

    std::shared_ptr<gdk::Model> pModel = std::make_shared<Model>([&]()
    {
        Model model("MySuperCoolModel",
            default_ptr<VertexData>(static_cast<std::shared_ptr<VertexData>>(VertexData::Cube)),
            default_ptr<ShaderProgram>(static_cast<std::shared_ptr<ShaderProgram>>(ShaderProgram::AlphaCutOff)));
            
        gdk::resources::local::fetchFile("resource/awesome.png",
        [&](const bool aSucceeded, std::vector<unsigned char> aData)
        {
            if (aSucceeded)
            {
                auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("awesome", aData));
                
                pModel.get()->setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex));
            }
            else gdk::log(TAG, "the fetch failed");
        });
        
        gdk::resources::local::fetchFile("resource/BG.png",
        [&](const bool aSucceeded, std::vector<unsigned char> aData)
        {
            if (aSucceeded)
            {
                auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("awesome", aData));
            
                pModel.get()->setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex));
            }
            else gdk::log(TAG, "the fetch failed");
        });
    
        resources::remote::fetchFile("https://jfcameron.updog.co/Public/mia.png",
        [&](const bool aSucceeded, std::vector<unsigned char> aData)
        {
            if (aSucceeded)
            {
                auto pTex = std::make_shared<gdk::Texture>(gdk::Texture("remote and not awesome", aData));

                pModel.get()->setTexture("_Texture", static_cast<std::shared_ptr<Texture>>(pTex));
            }
            else gdk::log(TAG, "the fetch failed");
        });

        model.setModelMatrix((Vector3){0., 0., 0.}, (Quaternion){});

        return model;
    }());

    models.push_back(pModel);

    ///////////////////////////

    gdk::Database db(gdk::Database::ConstructionMode::OPEN_OR_CREATE, gdk::Database::ReadMode::READWRITE, "very_cool_scene.db");

    std::string tableName = "Entities";
    
    Database::row_format_type tableFormat = {
        {"name", Database::Data::Type::Text},

        {"transform_position_x", Database::Data::Type::Real},
        {"transform_position_y", Database::Data::Type::Real},
        {"transform_position_z", Database::Data::Type::Real},

        {"transform_rotation_x", Database::Data::Type::Real},
        {"transform_rotation_y", Database::Data::Type::Real},
        {"transform_rotation_z", Database::Data::Type::Real},
    };

    db.createTable(tableName, tableFormat);

    db.writeToTable(tableName, (std::vector<Database::Data>){
        {Database::Data::text_type("Stevie")},
        
        {Database::Data::real_type(10.0)},
        {Database::Data::real_type(13.333)},
        {Database::Data::real_type(25.9541)},

        {Database::Data::real_type(35)},
        {Database::Data::real_type(42.5)},
        {Database::Data::real_type(16.66)},
    });

    auto table = db.getTableContents(tableName);

    class Entity
    {
    public:
        std::string m_Name = "Unknown";

        struct
        {
            struct
            {
                float x = 0, y = 0, z = 0;
            } m_Position;

            struct
            {
                float x = 0, y = 0, z = 0;
            } m_Rotation;
        } m_Transform;
    };

    struct : public Entity
    {

    } MyEntity = {};
    {
        const auto &firstRow = table[0];

        size_t i = 0;

        MyEntity.m_Name = firstRow[i++].getText();

        MyEntity.m_Transform.m_Position.x = firstRow[i++].getReal();
        MyEntity.m_Transform.m_Position.y = firstRow[i++].getReal();
        MyEntity.m_Transform.m_Position.z = firstRow[i++].getReal();
        
        MyEntity.m_Transform.m_Rotation.x = firstRow[i++].getReal();
        MyEntity.m_Transform.m_Rotation.y = firstRow[i++].getReal();
        MyEntity.m_Transform.m_Rotation.z = firstRow[i++].getReal();
    }

    std::cout << MyEntity.m_Name << std::endl;

    std::cout << "number of tables in database: " << db.getNumberOfTables() << std::endl;

    const auto tableNames = db.getTableNames();

    for (const auto &item : tableNames) std::cout << item << std::endl;

    const auto printTableExists = [&](const std::string &aTableName)
    {
        db.doesTableExist(aTableName) 
            ? std::cout << aTableName << " exists" << std::endl 
            : std::cout << aTableName << " does not exist!" << std::endl;
    };

    printTableExists(tableName);
    printTableExists("blimblam");

    //////////////////////////////

    gdk::GameLoop::Create(
        // Main Update
        [&](const double &aDeltaTime)
        {
            resources::hidden::updateResponseQueue();

            static Vector3 pos({0., 0. , -10.});
            static Vector3 sca({1., 0.5,   1.});
            static Quaternion rot;

            sca.z = sin(time::sinceStart() / 2.f) * 1.f;
            rot.setFromEuler({time::sinceStart() / 2.f, time::sinceStart(), 0});

            if (keyboard::getKeyDown(keyboard::Key::W)) pos.z -= 0.5;
            if (keyboard::getKeyDown(keyboard::Key::S)) pos.z += 0.5;
            if (keyboard::getKeyDown(keyboard::Key::A)) pos.x -= 0.5;
            if (keyboard::getKeyDown(keyboard::Key::D)) pos.x += 0.5;
            
            pModel->setModelMatrix(pos, rot, sca);
        },
        // Main Draw
        [&](const double &aDeltaTime)
        {
            for (std::shared_ptr<gdk::Camera> &camera : cameras) camera->draw(aDeltaTime, glfw::GetWindowSize(), models);
        },
        // Worker Update
        [&]()
        {
            resources::hidden::updateFetchQueue();
        }
    );
}
