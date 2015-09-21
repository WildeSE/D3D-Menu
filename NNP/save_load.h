HRESULT APIENTRY SaveLoad()
{
	while (1)
	{
		if (Fun.Fun1 == 1)
		{
			Save(Sett, "Анти отдача", Fun.отдача, Patch);
			Save(Sett, "Вертикальная стрельба", Fun.верт_стрельба, Patch);
			Save(Sett, "Откл.ожидание удара ножа[ПКМ]", Fun.откл_нож, Patch);
			Save(Sett, "Быстрая смена", Fun.offperezed, Patch);
			Save(Sett, "Быстрый нож", Fun.нож, Patch);
			Save(Sett, "Кросхаир", Fun.кросхаир, Patch);
			Save(Sett, "Гравитация", Fun.гравитация, Patch);
			Save(Sett, "Проход через обёкты", Fun.проход, Patch);
			Save(Sett, "Вниз под карту", Fun.карта, Patch);
			Save(Sett, "Бекс. бег", Fun.maxbeg, Patch);
			Save(Sett, "2Д Есп", Fun.кубик, Patch);
			Save(Sett, "Дистанция", Fun.дистанция, Patch);
			Save(Sett, "Линии", Fun.линии, Patch);
		}
		if (Fun.Fun2 == 1)
		{
			Fun.отдача = Load(Sett, "Анти отдача", Fun.отдача, Patch);
			Fun.верт_стрельба = Load(Sett, "Вертикальная стрельба", Fun.верт_стрельба, Patch);
			Fun.откл_нож = Load(Sett, "Откл.ожидание удара ножа[ПКМ]", Fun.откл_нож, Patch);
			Fun.offperezed = Load(Sett, "Быстрая смена", Fun.offperezed, Patch);
			Fun.нож = Load(Sett, "Быстрый нож", Fun.нож, Patch);
			Fun.кросхаир = Load(Sett, "Кросхаир", Fun.кросхаир, Patch);
			Fun.гравитация = Load(Sett, "Графитация", Fun.гравитация, Patch);
			Fun.проход = Load(Sett, "Проход через обёкты", Fun.проход, Patch);
			Fun.карта = Load(Sett, "Карта", Fun.карта, Patch);
			Fun.maxbeg = Load(Sett, "Бекс. бег", Fun.maxbeg, Patch);
			Fun.кубик = Load(Sett, "2Д Есп", Fun.кубик, Patch);
			Fun.дистанция = Load(Sett, "Дистанция", Fun.дистанция, Patch);
			Fun.линии = Load(Sett, "Линии", Fun.линии, Patch);
		}
		Sleep(500);
	}
}