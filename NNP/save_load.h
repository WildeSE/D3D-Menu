HRESULT APIENTRY SaveLoad()
{
	while (1)
	{
		if (Fun.Fun1 == 1)
		{
			Save(Sett, "���� ������", Fun.������, Patch);
			Save(Sett, "������������ ��������", Fun.����_��������, Patch);
			Save(Sett, "����.�������� ����� ����[���]", Fun.����_���, Patch);
			Save(Sett, "������� �����", Fun.offperezed, Patch);
			Save(Sett, "������� ���", Fun.���, Patch);
			Save(Sett, "��������", Fun.��������, Patch);
			Save(Sett, "����������", Fun.����������, Patch);
			Save(Sett, "������ ����� �����", Fun.������, Patch);
			Save(Sett, "���� ��� �����", Fun.�����, Patch);
			Save(Sett, "����. ���", Fun.maxbeg, Patch);
			Save(Sett, "2� ���", Fun.�����, Patch);
			Save(Sett, "���������", Fun.���������, Patch);
			Save(Sett, "�����", Fun.�����, Patch);
		}
		if (Fun.Fun2 == 1)
		{
			Fun.������ = Load(Sett, "���� ������", Fun.������, Patch);
			Fun.����_�������� = Load(Sett, "������������ ��������", Fun.����_��������, Patch);
			Fun.����_��� = Load(Sett, "����.�������� ����� ����[���]", Fun.����_���, Patch);
			Fun.offperezed = Load(Sett, "������� �����", Fun.offperezed, Patch);
			Fun.��� = Load(Sett, "������� ���", Fun.���, Patch);
			Fun.�������� = Load(Sett, "��������", Fun.��������, Patch);
			Fun.���������� = Load(Sett, "����������", Fun.����������, Patch);
			Fun.������ = Load(Sett, "������ ����� �����", Fun.������, Patch);
			Fun.����� = Load(Sett, "�����", Fun.�����, Patch);
			Fun.maxbeg = Load(Sett, "����. ���", Fun.maxbeg, Patch);
			Fun.����� = Load(Sett, "2� ���", Fun.�����, Patch);
			Fun.��������� = Load(Sett, "���������", Fun.���������, Patch);
			Fun.����� = Load(Sett, "�����", Fun.�����, Patch);
		}
		Sleep(500);
	}
}