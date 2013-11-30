
// AM2 Functions (for ReadAMAddress)
// *********************************

UINT32 am2Register()
{
	amFlag = 1;
	amOut = modVal & 0x1F;
	return 1;
}

UINT32 am2RegisterIndirect()
{
	amFlag = 0;
	amOut = v60.reg[modVal & 0x1F];
	return 1;
}

UINT32 bam2RegisterIndirect()
{
	amFlag = 0;
	amOut = v60.reg[modVal & 0x1F];
	bamOffset = 0;
	return 1;
}

UINT32 am2RegisterIndirectIndexed()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = v60.reg[modVal2 & 0x1F] + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = v60.reg[modVal2 & 0x1F] + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = v60.reg[modVal2 & 0x1F] + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = v60.reg[modVal2 & 0x1F] + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 2;
}

UINT32 bam2RegisterIndirectIndexed()
{
	amFlag = 0;
	amOut = v60.reg[modVal2 & 0x1F];
	bamOffset = v60.reg[modVal & 0x1F];
	return 2;
}

UINT32 am2Autoincrement()
{
	amFlag = 0;
	amOut = v60.reg[modVal & 0x1F];

	switch (modDim)
	{
	case 0:
		v60.reg[modVal & 0x1F] += 1;
		break;
	case 1:
		v60.reg[modVal & 0x1F] += 2;
		break;
	case 2:
		v60.reg[modVal & 0x1F] += 4;
		break;
	case 3:
		v60.reg[modVal & 0x1F] += 8;
		break;
	}

	return 1;
}

UINT32 bam2Autoincrement()
{
	amFlag = 0;
	amOut = v60.reg[modVal & 0x1F];
	bamOffset = 0;

	switch (modDim)
	{
	case 10:
		v60.reg[modVal & 0x1F] +=1;
		break;
	case 11:
		v60.reg[modVal & 0x1F] +=4;
		break;
	default:
		fatalerror("CPU - AM2 - 7 (t0 PC=%x)", PC);
		break;
	}

	return 1;
}

UINT32 am2Autodecrement()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		v60.reg[modVal & 0x1F] -= 1;
		break;
	case 1:
		v60.reg[modVal & 0x1F] -= 2;
		break;
	case 2:
		v60.reg[modVal & 0x1F] -= 4;
		break;
	case 3:
		v60.reg[modVal & 0x1F] -= 8;
		break;
	}

	amOut = v60.reg[modVal & 0x1F];
	return 1;
}

UINT32 bam2Autodecrement()
{
	amFlag = 0;
	bamOffset = 0;

	switch (modDim)
	{
	case 10:
		v60.reg[modVal & 0x1F]-=1;
		break;
	case 11:
		v60.reg[modVal & 0x1F]-=4;
		break;
	default:
		fatalerror("CPU - BAM2 - 7 (PC=%06x)", PC);
		break;
	}

	amOut = v60.reg[modVal & 0x1F];
	return 1;
}


UINT32 am2Displacement8()
{
	amFlag = 0;
	amOut = v60.reg[modVal & 0x1F] + (INT8)MemRead8(modAdd + 1);

	return 2;
}

UINT32 bam2Displacement8()
{
	amFlag = 0;
	amOut = v60.reg[modVal & 0x1F];
	bamOffset = (INT8)MemRead8(modAdd + 1);

	return 2;
}

UINT32 am2Displacement16()
{
	amFlag = 0;
	amOut = v60.reg[modVal & 0x1F] + (INT16)MemRead16(modAdd + 1);

	return 3;
}

UINT32 bam2Displacement16()
{
	amFlag = 0;
	amOut = v60.reg[modVal & 0x1F];
	bamOffset = (INT16)MemRead16(modAdd + 1);

	return 3;
}

UINT32 am2Displacement32()
{
	amFlag = 0;
	amOut = v60.reg[modVal & 0x1F] + MemRead32(modAdd + 1);

	return 5;
}

UINT32 bam2Displacement32()
{
	amFlag = 0;
	amOut = v60.reg[modVal & 0x1F];
	bamOffset = MemRead32(modAdd + 1);

	return 5;
}

UINT32 am2DisplacementIndexed8()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = v60.reg[modVal2 & 0x1F] + (INT8)MemRead8(modAdd + 2) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = v60.reg[modVal2 & 0x1F] + (INT8)MemRead8(modAdd + 2) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = v60.reg[modVal2 & 0x1F] + (INT8)MemRead8(modAdd + 2) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = v60.reg[modVal2 & 0x1F] + (INT8)MemRead8(modAdd + 2) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 3;
}

UINT32 bam2DisplacementIndexed8()
{
	amFlag = 0;
	amOut = v60.reg[modVal2 & 0x1F] + (INT8)MemRead8(modAdd + 2);
	bamOffset = v60.reg[modVal & 0x1F];

	return 3;
}

UINT32 am2DisplacementIndexed16()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = v60.reg[modVal2 & 0x1F] + (INT16)MemRead16(modAdd + 2) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = v60.reg[modVal2 & 0x1F] + (INT16)MemRead16(modAdd + 2) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = v60.reg[modVal2 & 0x1F] + (INT16)MemRead16(modAdd + 2) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = v60.reg[modVal2 & 0x1F] + (INT16)MemRead16(modAdd + 2) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 4;
}

UINT32 bam2DisplacementIndexed16()
{
	amFlag = 0;
	amOut = v60.reg[modVal2 & 0x1F] + (INT16)MemRead16(modAdd + 2);
	bamOffset = v60.reg[modVal & 0x1F];

	return 4;
}

UINT32 am2DisplacementIndexed32()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = v60.reg[modVal2 & 0x1F] + MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = v60.reg[modVal2 & 0x1F] + MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = v60.reg[modVal2 & 0x1F] + MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = v60.reg[modVal2 & 0x1F] + MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 6;
}

UINT32 bam2DisplacementIndexed32()
{
	amFlag = 0;
	amOut = v60.reg[modVal2 & 0x1F] + MemRead32(modAdd + 2);
	bamOffset = v60.reg[modVal & 0x1F];

	return 6;
}

UINT32 am2PCDisplacement8()
{
	amFlag = 0;
	amOut = PC + (INT8)MemRead8(modAdd + 1);

	return 2;
}

UINT32 bam2PCDisplacement8()
{
	amFlag = 0;
	amOut = PC;
	bamOffset = (INT8)MemRead8(modAdd + 1);

	return 2;
}

UINT32 am2PCDisplacement16()
{
	amFlag = 0;
	amOut = PC + (INT16)MemRead16(modAdd + 1);

	return 3;
}

UINT32 bam2PCDisplacement16()
{
	amFlag = 0;
	amOut = PC;
	bamOffset = (INT16)MemRead16(modAdd + 1);

	return 3;
}

UINT32 am2PCDisplacement32()
{
	amFlag = 0;
	amOut = PC + MemRead32(modAdd + 1);

	return 5;
}

UINT32 bam2PCDisplacement32()
{
	amFlag = 0;
	amOut = PC;
	bamOffset = MemRead32(modAdd + 1);

	return 5;
}


UINT32 am2PCDisplacementIndexed8()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = PC + (INT8)MemRead8(modAdd + 2) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = PC + (INT8)MemRead8(modAdd + 2) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = PC + (INT8)MemRead8(modAdd + 2) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = PC + (INT8)MemRead8(modAdd + 2) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 3;
}

UINT32 bam2PCDisplacementIndexed8()
{
	amFlag = 0;
	amOut = PC + (INT8)MemRead8(modAdd + 2);
	bamOffset = v60.reg[modVal & 0x1F];

	return 3;
}

UINT32 am2PCDisplacementIndexed16()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = PC + (INT16)MemRead16(modAdd + 2) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = PC + (INT16)MemRead16(modAdd + 2) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = PC + (INT16)MemRead16(modAdd + 2) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = PC + (INT16)MemRead16(modAdd + 2) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 4;
}

UINT32 bam2PCDisplacementIndexed16()
{
	amFlag = 0;
	amOut = PC + (INT16)MemRead16(modAdd + 2);
	bamOffset = v60.reg[modVal & 0x1F];

	return 4;
}

UINT32 am2PCDisplacementIndexed32()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = PC + MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = PC + MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = PC + MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = PC + MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 6;
}

UINT32 bam2PCDisplacementIndexed32()
{
	amFlag = 0;
	amOut = PC + MemRead32(modAdd + 2);
	bamOffset = v60.reg[modVal & 0x1F];

	return 6;
}

UINT32 am2DisplacementIndirect8()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + (INT8)MemRead8(modAdd + 1));

	return 2;
}

UINT32 bam2DisplacementIndirect8()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + (INT8)MemRead8(modAdd + 1));
	bamOffset = 0;
	return 2;
}

UINT32 am2DisplacementIndirect16()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + (INT16)MemRead16(modAdd + 1));

	return 3;
}

UINT32 bam2DisplacementIndirect16()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + (INT16)MemRead16(modAdd + 1));
	bamOffset = 0;
	return 3;
}

UINT32 am2DisplacementIndirect32()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + MemRead32(modAdd + 1));

	return 5;
}

UINT32 bam2DisplacementIndirect32()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + MemRead32(modAdd + 1));
	bamOffset = 0;

	return 5;
}

UINT32 am2DisplacementIndirectIndexed8()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + (INT8)MemRead8(modAdd + 2)) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + (INT8)MemRead8(modAdd + 2)) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + (INT8)MemRead8(modAdd + 2)) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + (INT8)MemRead8(modAdd + 2)) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 3;
}

UINT32 bam2DisplacementIndirectIndexed8()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal2 & 0x1F] + (INT8)MemRead8(modAdd + 2));
	bamOffset = v60.reg[modVal & 0x1F];

	return 3;
}

UINT32 am2DisplacementIndirectIndexed16()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + (INT16)MemRead16(modAdd + 2)) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + (INT16)MemRead16(modAdd + 2)) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + (INT16)MemRead16(modAdd + 2)) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + (INT16)MemRead16(modAdd + 2)) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 4;
}

UINT32 bam2DisplacementIndirectIndexed16()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal2 & 0x1F] + (INT16)MemRead16(modAdd + 2));
	bamOffset = v60.reg[modVal & 0x1F];

	return 4;
}

UINT32 am2DisplacementIndirectIndexed32()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = MemRead32(v60.reg[modVal2 & 0x1F] + MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 6;
}

UINT32 bam2DisplacementIndirectIndexed32()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal2 & 0x1F] + MemRead32(modAdd + 2));
	bamOffset = v60.reg[modVal & 0x1F];

	return 6;
}

UINT32 am2PCDisplacementIndirect8()
{
	amFlag = 0;
	amOut = MemRead32(PC + (INT8)MemRead8(modAdd + 1));

	return 2;
}

UINT32 bam2PCDisplacementIndirect8()
{
	amFlag = 0;
	amOut = MemRead32(PC + (INT8)MemRead8(modAdd + 1));
	bamOffset = 0;

	return 2;
}

UINT32 am2PCDisplacementIndirect16()
{
	amFlag = 0;
	amOut = MemRead32(PC + (INT16)MemRead16(modAdd + 1));

	return 3;
}

UINT32 bam2PCDisplacementIndirect16()
{
	amFlag = 0;
	amOut = MemRead32(PC + (INT16)MemRead16(modAdd + 1));
	bamOffset = 0;

	return 3;
}

UINT32 am2PCDisplacementIndirect32()
{
	amFlag = 0;
	amOut = MemRead32(PC + MemRead32(modAdd + 1));

	return 5;
}

UINT32 bam2PCDisplacementIndirect32()
{
	amFlag = 0;
	amOut = MemRead32(PC + MemRead32(modAdd + 1));
	bamOffset = 0;

	return 5;
}

UINT32 am2PCDisplacementIndirectIndexed8()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = MemRead32(PC + (INT8)MemRead8(modAdd + 2)) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = MemRead32(PC + (INT8)MemRead8(modAdd + 2)) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = MemRead32(PC + (INT8)MemRead8(modAdd + 2)) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = MemRead32(PC + (INT8)MemRead8(modAdd + 2)) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 3;
}

UINT32 bam2PCDisplacementIndirectIndexed8()
{
	amFlag = 0;
	amOut = MemRead32(PC + (INT8)MemRead8(modAdd + 2));
	bamOffset = v60.reg[modVal & 0x1F];

	return 3;
}

UINT32 am2PCDisplacementIndirectIndexed16()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = MemRead32(PC + (INT16)MemRead16(modAdd + 2)) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = MemRead32(PC + (INT16)MemRead16(modAdd + 2)) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = MemRead32(PC + (INT16)MemRead16(modAdd + 2)) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = MemRead32(PC + (INT16)MemRead16(modAdd + 2)) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 4;
}


UINT32 bam2PCDisplacementIndirectIndexed16()
{
	amFlag = 0;
	amOut = MemRead32(PC + (INT16)MemRead16(modAdd + 2));
	bamOffset = v60.reg[modVal & 0x1F];

	return 4;
}


UINT32 am2PCDisplacementIndirectIndexed32()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = MemRead32(PC + MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = MemRead32(PC + MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = MemRead32(PC + MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = MemRead32(PC + MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 6;
}

UINT32 bam2PCDisplacementIndirectIndexed32()
{
	amFlag = 0;
	amOut = MemRead32(PC + MemRead32(modAdd + 2));
	bamOffset = v60.reg[modVal & 0x1F];

	return 6;
}

UINT32 am2DoubleDisplacement8()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + (INT8)MemRead8(modAdd + 1)) + (INT8)MemRead8(modAdd + 2);

	return 3;
}

UINT32 bam2DoubleDisplacement8()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + (INT8)MemRead8(modAdd + 1));
	bamOffset = (INT8)MemRead8(modAdd + 2);

	return 3;
}

UINT32 am2DoubleDisplacement16()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + (INT16)MemRead16(modAdd + 1)) + (INT16)MemRead16(modAdd + 3);

	return 5;
}

UINT32 bam2DoubleDisplacement16()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + (INT16)MemRead16(modAdd + 1));
	bamOffset = (INT8)MemRead8(modAdd + 3);

	return 5;
}

UINT32 am2DoubleDisplacement32()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + MemRead32(modAdd + 1)) + MemRead32(modAdd + 5);

	return 9;
}

UINT32 bam2DoubleDisplacement32()
{
	amFlag = 0;
	amOut = MemRead32(v60.reg[modVal & 0x1F] + MemRead32(modAdd + 1));
	bamOffset = MemRead32(modAdd + 5);

	return 9;
}


UINT32 am2PCDoubleDisplacement8()
{
	amFlag = 0;
	amOut = MemRead32(PC + (INT8)MemRead8(modAdd + 1)) + (INT8)MemRead8(modAdd + 2);

	return 3;
}

UINT32 bam2PCDoubleDisplacement8()
{
	amFlag = 0;
	amOut = MemRead32(PC + (INT8)MemRead8(modAdd + 1));
	bamOffset = (INT8)MemRead8(modAdd + 2);

	return 3;
}

UINT32 am2PCDoubleDisplacement16()
{
	amFlag = 0;
	amOut = MemRead32(PC + (INT16)MemRead16(modAdd + 1)) + (INT16)MemRead16(modAdd + 3);

	return 5;
}

UINT32 bam2PCDoubleDisplacement16()
{
	amFlag = 0;
	amOut = MemRead32(PC + (INT16)MemRead16(modAdd + 1));
	bamOffset = (INT8)MemRead8(modAdd + 3);

	return 5;
}

UINT32 am2PCDoubleDisplacement32()
{
	amFlag = 0;
	amOut = MemRead32(PC + MemRead32(modAdd + 1)) + MemRead32(modAdd + 5);

	return 9;
}

UINT32 bam2PCDoubleDisplacement32()
{
	amFlag = 0;
	amOut = MemRead32(PC + MemRead32(modAdd + 1));
	bamOffset = MemRead32(modAdd + 5);

	return 9;
}

UINT32 am2DirectAddress()
{
	amFlag = 0;
	amOut = MemRead32(modAdd + 1);

	return 5;
}

UINT32 bam2DirectAddress()
{
	amFlag = 0;
	amOut = MemRead32(modAdd + 1);
	bamOffset = 0;

	return 5;
}

UINT32 am2DirectAddressIndexed()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = MemRead32(modAdd + 2) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 6;
}

UINT32 bam2DirectAddressIndexed()
{
	amFlag = 0;
	amOut = MemRead32(modAdd + 2);
	bamOffset = v60.reg[modVal & 0x1F];

	return 6;
}

UINT32 am2DirectAddressDeferred()
{
	amFlag = 0;
	amOut = MemRead32(MemRead32(modAdd + 1));

	return 5;
}

UINT32 bam2DirectAddressDeferred()
{
	amFlag = 0;
	amOut = MemRead32(MemRead32(modAdd + 1));
	bamOffset = 0;

	return 5;
}

UINT32 am2DirectAddressDeferredIndexed()
{
	amFlag = 0;

	switch (modDim)
	{
	case 0:
		amOut = MemRead32(MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F];
		break;
	case 1:
		amOut = MemRead32(MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F] * 2;
		break;
	case 2:
		amOut = MemRead32(MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F] * 4;
		break;
	case 3:
		amOut = MemRead32(MemRead32(modAdd + 2)) + v60.reg[modVal & 0x1F] * 8;
		break;
	}

	return 6;
}

UINT32 bam2DirectAddressDeferredIndexed()
{
	amFlag = 0;
	amOut = MemRead32(MemRead32(modAdd + 2));
	bamOffset = v60.reg[modVal & 0x1F];

	return 6;
}

UINT32 am2Immediate()
{
	// ignore LDPR
	return am1Immediate();
}

UINT32 am2ImmediateQuick()
{
	// ignore LDPR
	return am1ImmediateQuick();
}


// AM2 Tables (for ReadAMAddress)
// ******************************

UINT32 am2Error1()
{
	fatalerror("CPU - AM2 - 1 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}

UINT32 am2Error2()
{
	fatalerror("CPU - AM2 - 2 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}

#ifdef UNUSED_FUNCTION
UINT32 am2Error3()
{
	fatalerror("CPU - AM2 - 3 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}
#endif

UINT32 am2Error4()
{
	fatalerror("CPU - AM2 - 4 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}

UINT32 am2Error5()
{
	fatalerror("CPU - AM2 - 5 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}

UINT32 bam2Error1()
{
	fatalerror("CPU - BAM2 - 1 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}

UINT32 bam2Error2()
{
	fatalerror("CPU - BAM2 - 2 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}

#ifdef UNUSED_FUNCTION
UINT32 bam2Error3()
{
	fatalerror("CPU - BAM2 - 3 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}
#endif

UINT32 bam2Error4()
{
	fatalerror("CPU - BAM2 - 4 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}

UINT32 bam2Error5()
{
	fatalerror("CPU - BAM2 - 5 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}

UINT32 bam2Error6()
{
	fatalerror("CPU - BAM2 - 6 (PC=%06x)", PC);
	return 0; /* never reached, fatalerror won't return */
}


UINT32 (*const AMTable2_G7a[16])(void) =
{
	am2PCDisplacementIndexed8,
	am2PCDisplacementIndexed16,
	am2PCDisplacementIndexed32,
	am2DirectAddressIndexed,
	am2Error5,
	am2Error5,
	am2Error5,
	am2Error5,
	am2PCDisplacementIndirectIndexed8,
	am2PCDisplacementIndirectIndexed16,
	am2PCDisplacementIndirectIndexed32,
	am2DirectAddressDeferredIndexed,
	am2Error5,
	am2Error5,
	am2Error5,
	am2Error5
};

UINT32 (*const BAMTable2_G7a[16])(void) =
{
	bam2PCDisplacementIndexed8,
	bam2PCDisplacementIndexed16,
	bam2PCDisplacementIndexed32,
	bam2DirectAddressIndexed,
	bam2Error5,
	bam2Error5,
	bam2Error5,
	bam2Error5,
	bam2PCDisplacementIndirectIndexed8,
	bam2PCDisplacementIndirectIndexed16,
	bam2PCDisplacementIndirectIndexed32,
	bam2DirectAddressDeferredIndexed,
	bam2Error5,
	bam2Error5,
	bam2Error5,
	bam2Error5
};

UINT32 am2Group7a()
{
	if (!(modVal2 & 0x10))
		return am2Error4();

	return AMTable2_G7a[modVal2 & 0xF]();
}

UINT32 bam2Group7a()
{
	if (!(modVal2 & 0x10))
		return bam2Error4();

	return BAMTable2_G7a[modVal2 & 0xF]();
}

UINT32 (*const AMTable2_G7[32])(void) =
{
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2ImmediateQuick,
	am2PCDisplacement8,
	am2PCDisplacement16,
	am2PCDisplacement32,
	am2DirectAddress,
	am2Immediate,
	am2Error2,
	am2Error2,
	am2Error2,
	am2PCDisplacementIndirect8,
	am2PCDisplacementIndirect16,
	am2PCDisplacementIndirect32,
	am2DirectAddressDeferred,
	am2PCDoubleDisplacement8,
	am2PCDoubleDisplacement16,
	am2PCDoubleDisplacement32,
	am2Error2
};

UINT32 (*const BAMTable2_G7[32])(void) =
{
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2Error6,
	bam2PCDisplacement8,
	bam2PCDisplacement16,
	bam2PCDisplacement32,
	bam2DirectAddress,
	bam2Error6,
	bam2Error2,
	bam2Error2,
	bam2Error2,
	bam2PCDisplacementIndirect8,
	bam2PCDisplacementIndirect16,
	bam2PCDisplacementIndirect32,
	bam2DirectAddressDeferred,
	bam2PCDoubleDisplacement8,
	bam2PCDoubleDisplacement16,
	bam2PCDoubleDisplacement32,
	bam2Error2
};

UINT32 (*const AMTable2_G6[8])(void) =
{
	am2DisplacementIndexed8,
	am2DisplacementIndexed16,
	am2DisplacementIndexed32,
	am2RegisterIndirectIndexed,
	am2DisplacementIndirectIndexed8,
	am2DisplacementIndirectIndexed16,
	am2DisplacementIndirectIndexed32,
	am2Group7a
};

UINT32 (*const BAMTable2_G6[8])(void) =
{
	bam2DisplacementIndexed8,
	bam2DisplacementIndexed16,
	bam2DisplacementIndexed32,
	bam2RegisterIndirectIndexed,
	bam2DisplacementIndirectIndexed8,
	bam2DisplacementIndirectIndexed16,
	bam2DisplacementIndirectIndexed32,
	bam2Group7a
};




UINT32 am2Group6()
{
	modVal2 = MemRead8(modAdd + 1);
	return AMTable2_G6[modVal2 >> 5]();
}
UINT32 bam2Group6()
{
	modVal2 = MemRead8(modAdd + 1);
	return BAMTable2_G6[modVal2 >> 5]();
}

UINT32 am2Group7()
{
	return AMTable2_G7[modVal & 0x1F]();
}
UINT32 bam2Group7()
{
	return BAMTable2_G7[modVal & 0x1F]();
}


UINT32 (*const AMTable2[2][8])(void) =
{
	{
		am2Displacement8,
		am2Displacement16,
		am2Displacement32,
		am2RegisterIndirect,
		am2DisplacementIndirect8,
		am2DisplacementIndirect16,
		am2DisplacementIndirect32,
		am2Group7
	},

	{
		am2DoubleDisplacement8,
		am2DoubleDisplacement16,
		am2DoubleDisplacement32,
		am2Register,
		am2Autoincrement,
		am2Autodecrement,
		am2Group6,
		am2Error1
	}
};

UINT32 (*const BAMTable2[2][8])(void) =
{
	{
		bam2Displacement8,
		bam2Displacement16,
		bam2Displacement32,
		bam2RegisterIndirect,
		bam2DisplacementIndirect8,
		bam2DisplacementIndirect16,
		bam2DisplacementIndirect32,
		bam2Group7
	},

	{
		bam2DoubleDisplacement8,
		bam2DoubleDisplacement16,
		bam2DoubleDisplacement32,
		bam2Error6,
		bam2Autoincrement,
		bam2Autodecrement,
		bam2Group6,
		bam2Error1
	}
};



