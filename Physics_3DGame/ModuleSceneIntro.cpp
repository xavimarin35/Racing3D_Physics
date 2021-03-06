#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	clock.Start();

	CreateWorld();

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	BuildingsCubes.Clear();
	PeopleCubes.Clear();
	DetailsCubes.Clear();
	RoadCubes.Clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	for (int i = 53; i < 59; i++) 
	{
		ChangeColors(i);
	}

	for (int i = 0; i < num_floors; i++)
	{
		FloorCubes[i]->Render();
	}

	for (int i = 0; i < num_limits; i++) 
	{
		LimitCubes[i]->Render();
	}

	for (int i = 0; i < num_roads; i++)
	{
		RoadCubes[i]->Render();
	}

	for (int i = 0; i < num_buildings; i++)
	{
		BuildingsCubes[i]->Render();
	}

	for (int i = 0; i < num_details; i++)
	{
		DetailsCubes[i]->Render();
	}

	for (int i = 0; i < num_people; i++)
	{
		PeopleCubes[i]->Render();
	}

	return UPDATE_CONTINUE;

}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateWorld()
{
	// Rendering floor and sky
	FloorsRender();

	// Rendering map limits
	LimitsRender();

	// Rendering the road limits
	RoadRender();

	// Rendering buildings and people
	BuildingsRender();
	PeopleRender();

	// Rendering other details
	DetailsRender();
}

void ModuleSceneIntro::FloorsRender() 
{
	num_floors = 2;

	BodySize FloorSize[2] = { {800, 1, 800}, {800, 1, 800} };

	vec3 FloorPosition[2] = { {0, 0, 0}, {0, 80, 0} };

	//BodyRotation FloorRotation[2] = { {-45, {0,1,0}}, {0, {0,1,0}} };

	for (int i = 0; i < num_floors; i++)
	{
		FloorCubes.PushBack(new Cube(FloorSize[i].sizeX, FloorSize[i].sizeY, FloorSize[i].sizeZ));
		FloorCubes[i]->SetPos(FloorPosition[i].x, FloorPosition[i].y, FloorPosition[i].z);
		//FloorCubes[i]->SetRotation(FloorRotation[i].angle, FloorRotation[i].axis_pos);
		if (i == 0) { FloorCubes[i]->color = Grey2; }
		else if (i == 1) { FloorCubes[i]->color = Blue2; }
		bodyFloorCubes.PushBack(App->physics->AddBody(*(FloorCubes[i]), 0.0f));
	}
}

void ModuleSceneIntro::LimitsRender() 
{
	num_limits = 4;

	BodySize LimitsSize[4] = { {2, 130, 800}, {2, 130, 800}, {800, 130 , 2}, {800, 130, 2} };
	vec3 LimitsPosition[4] = { {-400, 15, 0}, {400, 15, 0}, {0, 15, 400}, {0, 15, -400} };

	for (int j = 0; j < num_limits; j++)
	{
		LimitCubes.PushBack(new Cube(LimitsSize[j].sizeX, LimitsSize[j].sizeY, LimitsSize[j].sizeZ));
		LimitCubes[j]->SetPos(LimitsPosition[j].x, LimitsPosition[j].y, LimitsPosition[j].z);
		LimitCubes[j]->color = Blue2;
		bodyLimitCubes.PushBack(App->physics->AddBody(*(LimitCubes[j]), 0.0f));
	}
}

void ModuleSceneIntro::RoadRender()
{
	num_roads = 62;

	BodySize curva_oberta = { 2,5,50 };
	BodySize curva_tancada = { 2,5,10 };

	//						  //   	recta 1      //          curva 1          //     recta 2      //             pont 1              //      recta 3     //         curva 2           //        recta 4     //           curva 3         //        recta 5     //          curva 4          //        recta 6     //          curva 5       //        recta 7     //         curva 6          //         recta 8    //         curva 7           //              pont 2          //        recta 9     //        recta 10   //        recta 11    //        recta 13    //      recta 12    //         curva 11          //       recta 14     //   recta auxiliar   //          curva 12        //        recta 15  //        recta 16  //  baixada  //  recta  //  recta 2 //  pujada //
	BodySize RoadSize[62] = { {2,5,100}, {2,5,100}, curva_oberta, curva_tancada, {2,5,15}, {2,5,15}, {15,2,23}, {32,2,23}, {15,2,23}, {2,5,100}, {2,5,100}, curva_oberta, curva_tancada, {2,5,150}, {2,5,143}, curva_oberta, curva_tancada, {2,5,400}, {2,5,422}, curva_oberta, curva_tancada, {2,5,400}, {2,5,460}, {2,5,50}, curva_tancada, {2,5,100}, {2,5,100}, curva_oberta, curva_tancada, {2,5,175}, {2,5,175}, curva_oberta, curva_tancada, {15,2,23}, {32,2,23}, {15,2,23}, {2,5,390}, {2,5,390}, {2,5,50}, {2,5,25}, {2,5,275}, {2,5,200}, {2,5,600}, {2,5,600}, {2,5,90}, {2,5,40}, curva_oberta, curva_tancada, {2,5,300}, {2,5,325}, {2,5,200}, {2,5,200}, curva_oberta, curva_tancada, {2,5,35}, {2,5,20}, {2,5,40}, {2,5,60}, {15,23,2}, {15,2,200}, {15,2,170}, {350,2,50} };

	//                        //      recta 1         //         curva 1        //          recta 2         //                       pont 1                      //            recta 3        //         curva 2          //            recta 4         //            curva 3            //           recta 5           //             curva 4             //            recta 6            //            curva 5            //           recta 7            //              curva 6          //             recta 8          //            curva 7            //                       pont 2                     //              recta 9        //            recta 10      //            recta 11         //          recta 13         //            recta 12        //              curva 11       //             recta 14         //            recta auxiliar     //               curva 12        //              recta 15           //             recta 16          //   baixada  //       recta  //     recta 2   //    pujada  //
	vec3 RoadPosition[62] = { {390,2.5,0}, {370,2.5,0}, {373,2.5,66}, {366,2.5,53}, {356,2.5,79}, {356,2.5,56}, {347.5,2.5,67.5}, {325,6.5,67.5}, {302.5,2.5,67.5}, {252,2.5,78}, {252,2.5,58}, {185,2.5,60}, {200,2.5,55}, {197,2.5,-23}, {167,2.5,-22.5}, {180,2.5,-115}, {164,2.5,-97.5}, {-38,2.5,-100}, {-40,2.5,-130}, {-270,2.5,-113}, {-241,2.5,-98}, {-243.5,2.5,105}, {-275,2.5,120}, {-258,2.5,340}, {-240,2.5,308}, {-187,2.5,311}, {-187,2.5,340}, {-120,2.5,323}, {-133,2.5,307.5}, {-100,2.5,217}, {-130,2.5,217}, {-113,2.5,111}, {-97,2.5,128}, {347.5,2.5,107.5}, {325,6.5,107.5}, {302.5,2.5,107.5}, {100,2.5,98}, {100,2.5,118}, {350,2.5,98}, {340,2.5,118}, {375,2.5,220}, {350,2.5,220}, {310,2.5,10}, {325,2.5,-10}, {347,2.5,337}, {337,2.5,305}, {308,2.5,-323}, {307,2.5,-292}, {155,2.5,-293}, {150,2.5,-320}, {-70,2.5,-292}, {-70,2.5,-320}, {-190,2.5,-302}, {-172,2.5,-291}, {-197,2.5,-275}, {-176,2.5,-280}, {-155,2.5,-270}, {-170,2.5,-256}, {380,6,-50}, {380,11.5,-159}, {295,11.5,-252}, {60,6,-250} };

	//                               //           recta 1      //             curva 1          //             recta 2           //                pont 1                  //             recta 3          //            curva 2          //          recta 4        //             curva 3           //              recta 5       //            curva 4           //          recta 6        //              curva 5          //             recta 7         //           curva 6          //          recta 8        //             curva 7          //                     pont 2               //           recta 9          //             recta 10           //          recta 11      //          recta 13       //            recta 12           //             curva 11          //            recta 14         //         recta auxiliar      //            curva 12          //          recta 15      //         recta 16          //     baixada  //      recta  //   recta 2  //   pujada  //
	BodyRotation RoadRotation[62] = { {0, {0,1,0}}, {0, {0,1,0}}, {-45, {0,1,0}}, {-45, {0,1,0}}, {-90, {0,1,0}}, {-90, {0,1,0}}, {-30, {0,0,1}}, {0, {0,1,0}}, {30,{0,0,1}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-135, {0,1,0}}, {-135,{0,1,0}}, {0, {0,1,0}}, {0,{0,1,0}}, {-135, {0,1,0}}, {-135,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-45, {0,1,0}}, {-45, {0,1,0}}, {0, {0,1,0}}, {0,{0,1,0}}, {-90, {0,1,0}}, {-135,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-45, {0,1,0}}, {-45, {0,1,0}}, {0, {0,1,0}}, {0,{0,1,0}}, {-45, {0,1,0}}, {-45, {0,1,0}}, {-30, {0,0,1}}, {0, {0,1,0}}, {30,{0,0,1}}, {-90,{0,1,0}}, {-89.5,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {0, {0,1,0}}, {0,{0,1,0}}, {0, {0,1,0}}, {0,{0,1,0}}, {-125, {0,1,0}}, {-140, {0,1,0}}, {-135, {0,1,0}}, {-135,{0,1,0}}, {-89.5,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-45, {0,1,0}}, {-45, {0,1,0}}, {0,{0,1,0}}, {0,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-60,{1,0,0}}, {0, {0,1,0}}, {-90,{0,1,0}}, {2,{0,0,1}} };

	for (int i = 0; i < num_roads; i++) 
	{
		RoadCubes.PushBack(new Cube(RoadSize[i].sizeX, RoadSize[i].sizeY, RoadSize[i].sizeZ));
		RoadCubes[i]->SetPos(RoadPosition[i].x, RoadPosition[i].y, RoadPosition[i].z);
		RoadCubes[i]->SetRotation(RoadRotation[i].angle, RoadRotation[i].axis_pos);
		RoadCubes[i]->color = DarkOrange;		
		bodyRoadCubes.PushBack(App->physics->AddBody(*(RoadCubes[i]), 0.0f));
	}
}

void ModuleSceneIntro::DetailsRender()
{
	num_details = 74;

	BodySize pas_zebra = { 4,2,20 };
	BodyRotation no_rotation = { 0,{0,1,0} };

	BodySize pal = { 2,15,2 };
	BodySize semafor = { 3,3,3 };

	BodySize DetailsSize[74] = { {2,10,2}, {2,10,2}, {18,3.3,2}, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pas_zebra, pal, pal, pal, pal, pal, pal, semafor, semafor, semafor, semafor, semafor, semafor, {0.2,0.2,0.2}, {0.2,0.2,0.2}, {1.6,0.2,0.2}, {1.6,0.2,0.2}, {0.2,1,0.2}, {0.2,0.9,0.2}, {1.6,0.2,0.2}, {1.6,0.2,0.2}, {0.2,2.1,0.2}, {0.2,1.1,0.2}, {0.2,2.1,0.2}, {0.2,2.1,0.2}, {1.3,0.2,0.2}, {1.3,0.2,0.2} };
	vec3 DetailsPosition[74] = { {390,10,15}, {370,10,15}, {380,13,15}, {182,-0.4,-23}, {188,-0.4,-23}, {176,-0.4,-23}, {170,-0.4,-23}, {194,-0.4,-23}, {100,-0.4,-116}, {100,-0.4,-110}, {100,-0.4,-122}, {100,-0.4,-128}, {100,-0.4,-103}, {-150,-0.4,-116}, {-150,-0.4,-110}, {-150,-0.4,-122}, {-150,-0.4,-128}, {-150,-0.4,-103}, {248,-0.4,107.2}, {248,-0.4,113.2}, {248,-0.4,101.2}, {137,-0.4,-306}, {137,-0.4,-300}, {137,-0.4,-294}, {137,-0.4,-312}, {137,-0.4,-318}, {-247.5,-0.4,0}, {-265.5,-0.4,0}, {-271.5,-0.4,0}, {-253.5,-0.4,0}, {-259.5,-0.4,0}, {-247.5,-0.4,200}, {-265.5,-0.4,200}, {-271.5,-0.4,200}, {-253.5,-0.4,200}, {-259.5,-0.4,200}, {362.5,-0.4,200}, {356.5,-0.4,200}, {350.5,-0.4,200}, {368.5,-0.4,200}, {374.5,-0.4,200}, {311,-0.4,-60}, {317,-0.4,-60}, {323,-0.4,-60}, {311,-0.4,-200}, {317,-0.4,-200}, {323,-0.4,-200}, {190,10,-110}, {-268.5,10,-115}, {-245,10,340.5}, {306,10,122}, {309,10,-320.5}, {-102,10,-277}, {190,19,-110}, {-268.5,19,-115}, {-245,19,340.5}, {306,19,122}, {309,19,-320.5}, {-102,19,-277}, {380,13.4,13.9}, {380,12.6,13.9}, {382.5,13.9,13.9}, {382.5,12,13.9}, {381.8,13.4,13.9}, {383.2,12.5,13.9}, {382.5,12.95,13.9}, {377.5,12.95,13.9}, {377.1,12.95,13.9}, {378.3,13.4,13.9}, {375.6,12.95,13.9}, {374.3,12.95,13.9}, {374.95,12,13.9}, {374.95,13.9,13.9} };
	BodyRotation DetailsRotation[74] = { no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, {-90,{0,1,0}}, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, {45,{0,1,0}}, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, {45,{0,1,0}}, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation };

	for (int i = 0; i < num_details; i++)
	{
		DetailsCubes.PushBack(new Cube(DetailsSize[i].sizeX, DetailsSize[i].sizeY, DetailsSize[i].sizeZ));
		DetailsCubes[i]->SetPos(DetailsPosition[i].x, DetailsPosition[i].y, DetailsPosition[i].z);
		DetailsCubes[i]->SetRotation(DetailsRotation[i].angle, DetailsRotation[i].axis_pos);
		if (i == 0 || i == 1)
		{
			DetailsCubes[i]->color = Black;
		}
		else if (i == 2)
		{
			DetailsCubes[i]->color = Yellow;
		}
		else if (i > 2 && i < 47)
		{
			DetailsCubes[i]->color = White;
		}
		else if (i >= 47 && i < 53)
		{
			DetailsCubes[i]->color = Yellow;
		}
		else if (i >= 53 && i < 74)
		{
			DetailsCubes[i]->color = Black;
		}
		bodyDetailsCubes.PushBack(App->physics->AddBody(*(DetailsCubes[i]), 0.0f));
	}
}

void ModuleSceneIntro::PeopleRender() 
{
	num_people = 51;
	BodyRotation no_rotation = { 0, {0,1,0} };
	BodySize face = { 1,1,1 };
	BodySize body = { 1.5,2.5,1 };

	BodySize PeopleSize[51] = { {}, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body, face, body };
	vec3 PeoplePosition[51] = { {}, {180,4.2,-23}, {180,2.5,-23}, {245,4.2,109}, {245,2.5,109}, {250,4.2,102}, {250,2.5,102}, {137,4.2,-312}, {137,2.5,-312}, {-143,4.2,-113}, {-143,2.5,-113}, {-266,4.2,3}, {-266,2.5,3}, {170,4.2,-20}, {170,2.5,-20}, {-250,4.2,200}, {-250,2.5,200}, {-260,4.2,190}, {-260,2.5,190}, {360,4.2,200}, {360,2.5,200}, {315,4.2,-60}, {315,2.5,-60}, {370,4.2,190}, {370,2.5,190}, {320,4.2,-195}, {320,2.5,-195}, {240,4.2,113}, {240,2.5,113}, {104,4.2,-117}, {104,2.5,-117}, {104,4.2,-106}, {104,2.5,-106}, {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{} };
	BodyRotation PeopleRotation[51] = { {}, no_rotation, no_rotation, {90,{0,1,0}}, {90,{0,1,0}}, {90,{0,1,0}}, {90,{0,1,0}}, {90,{0,1,0}}, {90,{0,1,0}}, {90,{0,1,0}}, {90,{0,1,0}}, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, no_rotation, {90,{0,1,0}}, {90,{0,1,0}}, {90,{0,1,0}}, {90,{0,1,0}}, {90,{0,1,0}}, {90,{0,1,0}} };

	for (int i = 0; i < num_people; i++) 
	{
		PeopleCubes.PushBack(new Cube(PeopleSize[i].sizeX, PeopleSize[i].sizeY, PeopleSize[i].sizeZ));
		PeopleCubes[i]->SetPos(PeoplePosition[i].x, PeoplePosition[i].y, PeoplePosition[i].z);
		PeopleCubes[i]->SetRotation(PeopleRotation[i].angle, PeopleRotation[i].axis_pos);
		bodyPeopleCubes.PushBack(App->physics->AddBody(*(PeopleCubes[i]), 0.0f));
		
		if (i % 2 == 0)
		{
			if (i > 0 && i < 12 || i > 26 && i < 38) 
			{
				PeopleCubes[i]->color = Green;
			}

			else PeopleCubes[i]->color = Red;
		}
		
		else
		{
			if (i > 0 && i < 12 || i > 38 && i <= 50) 
			{
				PeopleCubes[i]->color = Skin2;
			}

			else PeopleCubes[i]->color = Skin;
		}
	}
}

void ModuleSceneIntro::BuildingsRender() 
{
	num_buildings = 121;

	BodySize littleBuilding = {15,50,15};
	BodySize midBuilding = {20,50,20};
	BodySize bigBuilding = {25,50,25};

	BodySize BuildingsSize[121] = { littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding, midBuilding, bigBuilding, littleBuilding };
	vec3 BuildingsPosition[121] = { {360,25,0}, {340,25,40}, {390,25,120}, {390,25,170}, {390,25,220}, {150,25,27}, {150,25,68}, {150,25,-30}, {150,25,-70}, {210,25,40}, {220,25,10}, {215,25,-20}, {215,25,-60}, {293,25,40}, {120,25,-85}, {-200,25,-85}, {95,25,-80}, {60,25,-85}, {0,25,-75}, {-35,25,-80}, {-70,25,-85}, {-110,25,-80}, {-145,25,-80}, {-173,25,-80}, {120,25,-145}, {-200,25,-145}, {95,25,-145}, {60,25,-145}, {0,25,-145}, {-35,25,-145}, {-70,25,-145}, {-110,25,-145}, {-145,25,-145}, {-173,25,-145}, {-230,25,-64}, {-230,25,-30}, {-230,25,0}, {-230,25,45}, {-230,25,75}, {-230,25,100}, {-230,25,140}, {-230,25,180}, {-230,25,225}, {-310,25,-64}, {-310,25,-30}, {-310,25,0}, {-310,25,45}, {-310,25,75}, {-310,25,100}, {-310,25,140}, {-310,25,180}, {-310,25,225}, {-230,25,250}, {-310,25,250}, {-150,25,290}, {-175,25,290}, {-200,25,290}, {-150,25,280}, {-150,25,240}, {-150,25,200}, {-150,25,165}, {-80,25,280}, {-80,25,240}, {-80,25,165}, {-80,25,200}, {285,25,280}, {285,25,250}, {285,25,210}, {285,25,180}, {285,25,150}, {290,25,15}, {290,25,-10}, {290,25,-45}, {290,25,-80}, {290,25,-110}, {290,25,-145}, {350,25,15}, {350,25,-10}, {350,25,-45}, {350,25,-80}, {350,25,-110}, {350,25,-145}, {280,25,-340}, {250,25,-340}, {200,25,-340}, {160,25,-340}, {120,25,-340}, {90,25,-340}, {55,25,-340}, {10,25,-340}, {-75,25,-340}, {-100,25,-340}, {-80,25,220}, {-55,25,220}, {-15,25,220}, {15,25,220}, {60,25,220}, {95,25,220}, {120,25,220}, {160,25,220}, {185,25,220}, {210,25,220}, {240,25,220}, {-250,25,360}, {-220,25,360}, {-180,25,360}, {-145,25,360}, {-120,25,360}, {-65,25,135}, {-25,25,135}, {10,25,135}, {50,25,135}, {90,25,135}, {140,25,135}, {180,25,135}, {-70,25,80}, {-20,25,80}, {20,25,80}, {60,25,80}, {100,25,80}, {125,25,80} };

	for (int i = 0; i < num_buildings; i++) 
	{
		BuildingsCubes.PushBack(new Cube(BuildingsSize[i].sizeX, BuildingsSize[i].sizeY, BuildingsSize[i].sizeZ));
		BuildingsCubes[i]->SetPos(BuildingsPosition[i].x, BuildingsPosition[i].y, BuildingsPosition[i].z);
		bodyBuildingsCubes.PushBack(App->physics->AddBody(*(BuildingsCubes[i]), 0.0f));
		if (i % 4 == 0) 
		{
			BuildingsCubes[i]->color = White;
		}
		else if (i % 3 == 0)
		{
			BuildingsCubes[i]->color = Grey;
		}
		else if (i % 2 == 0) 
		{
			BuildingsCubes[i]->color = Grey2;
		}
		else BuildingsCubes[i]->color = Grey3;
	}
}

void ModuleSceneIntro::ChangeColors(int i) 
{
	// Checkpoint 2
	if (i == 53)
	{
		if (App->player->checkpoint2 == false)
		{
			DetailsCubes[i]->color = Red;
		}
		else DetailsCubes[i]->color = Green;
	}

	// Checkpoint 3
	if (i == 54)
	{
		if (App->player->checkpoint3 == false)
		{
			DetailsCubes[i]->color = Red;
		}
		else DetailsCubes[i]->color = Green;
	}

	// Checkpoint 4
	if (i == 55)
	{
		if (App->player->checkpoint4 == false)
		{
			DetailsCubes[i]->color = Red;
		}
		else DetailsCubes[i]->color = Green;
	}

	// Checkpoint 5
	if (i == 56)
	{
		if (App->player->checkpoint5 == false)
		{
			DetailsCubes[i]->color = Red;
		}
		else DetailsCubes[i]->color = Green;
	}

	// Checkpoint 6
	if (i == 57)
	{
		if (App->player->checkpoint6 == false)
		{
			DetailsCubes[i]->color = Red;
		}
		else DetailsCubes[i]->color = Green;
	}

	// Checkpoint 7
	if (i == 58)
	{
		if (App->player->checkpoint7 == false)
		{
			DetailsCubes[i]->color = Red;
		}
		else DetailsCubes[i]->color = Green;
	}
}